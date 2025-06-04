#include <Diophant/machine.hpp>
#include <Diophant/values/list.hpp>
#include <Diophant/values/lambda.hpp>
#include <Diophant/values/struct.hpp>
#include <Diophant/values/leaf.hpp>

namespace Diophant {

    LogStream cout {};

    machine::result machine::evaluate (program p) const {
        machine::result r {*this, expression {}};
        program pp = p;

        while (!data::empty (pp)) {
            r = r.Machine.evaluate (data::first (pp));
            pp = data::rest (pp);
        }

        return r;
    }

    machine::result machine::evaluate (const statement &x) const {
        if (!bool (x.Subject)) return {*this, evaluate (x.Predicate)};

        type of {};
        expression as = x.Predicate;

        const form *e = x.Predicate.get ();
        if (e != nullptr) {
            const node *nn = dynamic_cast<const node *> (e);
            if (nn == nullptr) throw data::exception {} << "invalid definition";

            const casted *xx = dynamic_cast<const casted *> (nn);
            if (xx != nullptr) {
                of = xx->Cast;
                as = xx->Def;
            }
        }

        const form *q = x.Subject->get ();

        const node *n = dynamic_cast<const node *> (q);
        if (n == nullptr) throw data::exception {} << "invalid definition";

        if (const symbol *p = dynamic_cast<const symbol *> (n); p != nullptr) {
            return {define (*p, of, as), expression {}};
        }

        if (const call *fx = dynamic_cast<const call *> (n); fx != nullptr) {
            expression fun;
            data::stack<data::stack<expression>> args;

            while (true) {
                fun = fx->Fun;
                args <<= fx->Args;

                const node *fn = dynamic_cast<const node *> (fun.get ());

                if (fn == nullptr) throw data::exception {} << "invalid definition";

                const symbol *z = dynamic_cast<const symbol *> (fn);

                if (z != nullptr) {
                    data::stack<pattern> drgs;

                    while (!data::empty (args)) {
                        drgs = drgs + data::stack<pattern> (data::reverse (data::first (args)));
                        args = data::rest (args);
                    }

                    drgs = data::reverse (drgs);

                    return {define (*z, of, drgs, as), expression {}};
                }

                fx = dynamic_cast<const call *> (fn);

                if (fx == nullptr) throw data::exception {} << "invalid definition";
            }
        }

        if (const unop *u = dynamic_cast<const unop *> (n); u != nullptr) {
            return {define (u->Operand, of, u->Body, as), expression {}};
        }

        if (const binop *b = dynamic_cast<const binop *> (n); b != nullptr) {
            if (b->Body.size () != 2) throw data::exception {} << "invalid definition";

            return {define (b->Operand, of, b->Body[0], b->Body[1], as), expression {}};
        }

        throw data::exception {} << "invalid definition";
    }

    namespace {
        machine::symbol_defs def (machine::symbol_defs, symbol x, type of, expression as);
        machine::symbol_defs def (Machine, machine::symbol_defs, symbol x, type of, data::stack<pattern> arg, expression as);
        machine::unary_defs def (Machine, machine::unary_defs, unary_operand op, type of, pattern arg, expression as);
        machine::binary_defs def (Machine, machine::binary_defs, binary_operand op, type of, pattern left, pattern right, expression as);
    }

    machine machine::define (symbol x, expression as) const {
        return machine {def (SymbolDefinitions, x, type {}, as), UnaryDefinitions, BinaryDefinitions};
    }

    machine machine::define (symbol x, data::stack<pattern> arg, expression as) const {
        return machine {def (*this, SymbolDefinitions, x, type {}, arg, as), UnaryDefinitions, BinaryDefinitions};
    }

    machine machine::define (symbol x, type of, expression as) const {
        return machine {def (SymbolDefinitions, x, of, as), UnaryDefinitions, BinaryDefinitions};
    }

    machine machine::define (symbol x, type of, data::stack<pattern> arg, expression as) const {
        return machine {def (*this, SymbolDefinitions, x, of, arg, as), UnaryDefinitions, BinaryDefinitions};
    }

    machine machine::define (unary_operand op, pattern in, expression as) const {
        return machine {SymbolDefinitions, def (*this, UnaryDefinitions, op, type {}, in, as), BinaryDefinitions};
    }

    machine machine::define (binary_operand op, pattern left, pattern right, expression as) const {
        return machine {SymbolDefinitions, UnaryDefinitions, def (*this, BinaryDefinitions, op, type {}, left, right, as)};
    }

    machine machine::define (unary_operand op, type of, pattern in, expression as) const {
        return machine {SymbolDefinitions, def (*this, UnaryDefinitions, op, of, in, as), BinaryDefinitions};
    }

    machine machine::define (binary_operand op, type of, pattern left, pattern right, expression as) const {
        return machine {SymbolDefinitions, UnaryDefinitions, def (*this, BinaryDefinitions, op, of, left, right, as)};
    }

    namespace {

        expression evaluate_round (const machine &m, const node &e);

    }

    // note: this algorithm results in attempts to evaluate
    // sub expressions over again that have not changed.
    // We might want to mark expressions as already having been
    // evaluated.
    expression machine::evaluate (Expression e) const {
        expression last = e;
        while (true) {
            const form *p = last.get ();
            if (p == nullptr) throw data::exception {} << "null expression evaluated";

            const node *n = dynamic_cast<const node *> (p);
            if (n == nullptr) throw data::exception {} << "not a node";

            // It is possible that this expression was already evaluated
            // ahead a few steps. If it was, we just go to the end.
            if (bool (n->Evaluated)) {
                if (n->Evaluated == expression {}) return last;
                last = *n->Evaluated;
                continue;
            }

            expression next = evaluate_round (*this, *n);

            // indicates that no evaluation occurred.
            if (next == expression {} || next.get () == last.get ()) {
                n->Evaluated = expression {};
                return last;
            }

            n->Evaluated = next;
            last = next;
        }
    }

    match_result machine::match (data::stack<pattern> p, data::stack<expression> e) const {
        if (data::size (p) != data::size (e)) return {no};

        replacements r;
        while (!data::empty (p)) {
            auto m = Diophant::match (*this, data::first (p), data::first (e));
            if (intuit (m) != yes) return m;
            try {
                r = r & *m;
            // will be thrown if these maps have any of the same keys.
            } catch (replacements::key_already_exists) {
                return {no};
            }

            p = data::rest (p);
            e = data::rest (e);
        }
        return r;
    }

    namespace {

        expression evaluate_symbol (const machine &m, const symbol &x);

        expression evaluate_list (const machine &m, const list &ls);

        expression evaluate_struct (const machine &m, const dstruct &);

        expression evaluate_binop (const machine &m, const binop &b);

        expression evaluate_unop (const machine &m, const unop &u);

        expression evaluate_call (const machine &m, const call &c);

        expression evaluate_if (const machine &m, const dif &);

        expression evaluate_let (const machine &m, const let &);

        expression evaluate_round (const machine &m, const node &n) {
            if (const symbol *x = dynamic_cast<const symbol *> (&n); x != nullptr)
                return evaluate_symbol (m, *x);

            if (const list *ls = dynamic_cast<const list *> (&n); ls != nullptr)
                return evaluate_list (m, *ls);

            if (const dstruct *s = dynamic_cast<const dstruct *> (&n); s != nullptr)
                return evaluate_struct (m, *s);

            if (const binop *b = dynamic_cast<const binop *> (&n); b != nullptr)
                return evaluate_binop (m, *b);

            if (const unop *u = dynamic_cast<const unop *> (&n); u != nullptr)
                return evaluate_unop (m, *u);

            if (const call *fx = dynamic_cast<const call *> (&n); fx != nullptr)
                return evaluate_call (m, *fx);

            if (const dif *df = dynamic_cast<const dif *> (&n); df != nullptr)
                return evaluate_if (m, *df);

            if (const let *l = dynamic_cast<const let *> (&n); l != nullptr)
                return evaluate_let (m, *l);

            return {};
        }

        using mtf = transformation;

        struct candidate {
            replacements Replacements;
            casted Result;
            data::stack<expression> Remaining;
        };

        // TODO we need an option for a set of automatic replacements.
        data::maybe<candidate> get_candidate (const machine &m, data::stack<mtf> tfs, data::stack<expression> args) {
            // we store a potential match here but continue searching to
            // ensure that we do not match twice.
            data::maybe<candidate> matched {};

            while (!data::empty (tfs)) {

                auto &tf = data::first (tfs);
                if (data::size (tf.Arguments) > data::size (args)) return {};

                auto match_args = data::take (args, data::size (tf.Arguments));
                match_result r = m.match (tf.Arguments, match_args);

                if (intuit (r) == yes) {
                    if (bool (matched)) throw data::exception {} << "no unique match";
                    matched = {{*r, tf.Value, data::drop (args, data::size (tf.Arguments))}};
                } else if (intuit (r) == unknown) {
                    throw data::exception {} << "we need to ensure that evaluation does not continue at this point";
                }

                tfs = data::rest (tfs);
            }

            return matched;
        }

        expression evaluate_list (const machine &m, const list &ls) {

            bool changed = false;
            data::stack<expression> new_ls;

            for (Expression old_arg : data::stack<expression> (ls.List)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != old_arg) changed = true;
                new_ls <<= new_arg;
            }

            return changed ? list::make (data::reverse (new_ls)) : expression {};
        }

        expression evaluate_struct (const machine &m, const dstruct &dst) {
            bool changed = false;
            data::stack<data::entry<symbol, expression>> new_dst;

            for (data::entry<symbol, expression> old : dst.Values) {
                data::entry<symbol, expression> new_e {old.Key, m.evaluate (old.Value)};
                if (new_e.Value != old.Value) changed = true;
                new_dst <<= new_e;
            }

            return changed ? dstruct::make (data::reverse (new_dst)) : expression {};
        }

        expression evaluate_symbol (const machine &m, const symbol &x) {

            const machine::definition *v = m.SymbolDefinitions.contains (x);
            if (v == nullptr) return {};

            if (!std::holds_alternative<casted> (*v)) return {};

            const casted &z = std::get<casted> (*v);

            if (!bool (z.Def)) return {};

            return z.Def;
        }

        expression evaluate_binop (const machine &m, const binop &b) {
            // first we evaluate function and args individually.
            bool changed = false;

            if (b.Operand == binary_operand::define)
                throw data::exception {} << "define operator found in expression. This is not allowed!";

            if (b.Operand == binary_operand::apply)
                return call::make (first (b.Body), rest (b.Body));

            data::list<expression> body;
            for (Expression old_arg : data::stack<expression> (b.Body)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != old_arg) changed = true;
                body <<= new_arg;
            }

            if (body.size () < 2) throw data::exception {"apply expression is too small (should be impossible)"};

            if (b.Operand == binary_operand::dot) {
                auto fst = first (body);
                auto snd = first (rest (body));
                if (const dstruct *ds = dynamic_cast<const dstruct *> (fst.get ()); ds != nullptr)
                    for (const auto &[name, val] : ds->Values)
                        if (const symbol *x = dynamic_cast<const symbol *> (snd.get ()); x != nullptr)
                            if (*x == name) return val;
            }

            if (const data::stack<mtf> *v = m.BinaryDefinitions.contains (b.Operand); v != nullptr) {

                data::stack<mtf> tfs = *v;

                if (data::maybe<candidate> cx = get_candidate (m, tfs, body); bool (cx)) {
                    changed = true;
                    if (cx->Result.Def == expression {})
                        throw data::exception {} << "Error: attempt to evaluate undefined pattern";
                    return m.evaluate (replace (cx->Result.Def, cx->Replacements));
                }
            }

            return changed ? binop::make (b.Operand, body) : expression {};
        }

        expression evaluate_unop (const machine &m, const unop &u) {
            // first we evaluate function and args individually.
            bool changed = false;
            expression body = m.evaluate (u.Body);
            if (body != u.Body) changed = true;

            {
                const data::stack<mtf> *v = m.UnaryDefinitions.contains (u.Operand);
                if (v == nullptr) goto done;

                data::stack<mtf> tfs = *v;
                data::maybe<candidate> cx = get_candidate (m, tfs, {body});

                if (bool (cx)) {
                    changed = true;
                    if (!bool (cx->Result.Def))
                        throw data::exception {} << "Error: attempt to evaluate undefined pattern";

                    return m.evaluate (replace (cx->Result.Def, cx->Replacements));
                }
            }

            done:
            return changed ? unop::make (u.Operand, body) : expression {};
        }

        // the strategy here is to evaluate the head of the expression first, then
        // evaluate all function calls. We evaluate arguments lazily, enough to
        // determine their types if needed. Once there are no more function calls
        // we can evaluate, we evaluate each of the arguments.
        expression evaluate_call (const machine &m, const call &c) {
            // first we evaluate function.
            bool changed = false;
            expression fun = m.evaluate (c.Fun);
            if (fun != c.Fun) changed = true;

            data::stack<expression> args = c.Args;

            // next we try to match the function and args against our definitions.
            while (true) {
                const form *p = fun.get ();

                if (p == nullptr) break;

                int min_args = 1;

                if (const call *fx = dynamic_cast<const call *> (p); fx != nullptr) {
                    // we will skip the definitions that have as many args as
                    // in the inner call or fewer, since these would
                    // have already been checked.

                    min_args += data::size (fx->Args);
                    args = data::reverse (args + data::reverse (fx->Args));
                    fun = fx->Fun;
                    p = fun.get ();
                    changed = true;
                }

                // if the head is a lambda, we can evaluate it completely lazily.
                if (const lambda *n = dynamic_cast<const lambda *> (p); n != nullptr) {
                    if (data::size (n->Args) > data::size (args)) break;

                    changed = true;
                    data::stack<symbol> in = n->Args;
                    replacements r;

                    while (!data::empty (in)) {
                        r = r.insert (data::first (in), data::first (args));
                        in = data::rest (in);
                        args = data::rest (args);
                    }

                    fun = m.evaluate (replace (n->Body, r));
                    if (data::empty (args)) return fun;
                    continue;
                }

                if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr) {
                    // look for definitions corresponding to this symbol.
                    const machine::definition *v = m.SymbolDefinitions.contains (*x);
                    if (v == nullptr || !std::holds_alternative<data::stack<mtf>> (*v)) break;

                    data::stack<mtf> tfs = std::get<data::stack<mtf>> (*v);
                    while (true) {
                        if (data::empty (tfs)) goto done;
                        if (data::size (data::first (tfs).Arguments) >= min_args) break;
                        tfs = data::rest (tfs);
                    }

                    data::maybe<candidate> cx = get_candidate (m, tfs, args);
                    if (bool (cx)) {
                        changed = true;
                        if (!bool (cx->Result.Def))
                            throw data::exception {} << "Error: attempt to evaluate undefined pattern";
                        fun = m.evaluate (replace (cx->Result.Def, cx->Replacements));
                        args = cx->Remaining;
                        if (args.size () == 0) return fun;
                        continue;
                    }

                    // in this case, we need to check if any of the arguments have been
                    // evaluated so that we can fast forward them.
                    if (!changed) {
                        data::stack<expression> new_args {};
                        for (Expression ex : args) {
                            expression next = ex;
                            while (true) {
                                if (const node *n = static_cast<const node *> (next.get ());
                                    n != nullptr && bool (n->Evaluated) && *n->Evaluated != expression {}) {
                                    changed = true;
                                    next = *n->Evaluated;
                                } else break;
                            }
                            new_args <<= next;
                        }
                        if (changed) args = data::reverse (new_args);
                        else return expression {};
                    }
                }

                if (const value *v = dynamic_cast<const value *> (p); v != nullptr) {
                    expression next = (*v) (args);
                    if (next != expression {}) return next;
                }

                break;
            }

            done:

            // evaluate all arguments.
            data::stack<expression> new_args {};
            for (Expression ex : args) {
                expression next = m.evaluate (ex);
                new_args <<= next;
                if (next != ex) changed = true;
            }

            args = data::reverse (new_args);

            return changed ? call::make (fun, args) : expression {};
        }

        expression evaluate_if (const machine &m, const dif &df) {
            auto If = m.evaluate (df.If);

            if (const boolean *xx = dynamic_cast<const boolean *> (If.get ()); xx != nullptr)
                return xx->Value ? df.Then : df.Else;

            if (const call *fx = dynamic_cast<const call *> (If.get ()); fx != nullptr) {
                if (fx->Args.size () != 1) return {};

                const symbol *f = dynamic_cast<const symbol *> (fx->Fun.get ());
                if (f == nullptr) return {};
                if (*f != symbol {"scriptnum"}) return {};

                const bytes *x = dynamic_cast<const bytes *> (fx->Args.first ().get ());
                if (x == nullptr) return {};

                return Bitcoin::nonzero (x->Value) ? df.Then : df.Else;
            }

            return {};
        }

        expression evaluate_let (const machine &m, const let &l) {
            return replace (l.In, data::fold ([] (auto &&r, auto &&v) {
                return r.insert (v.Key, replace (v.Value, r));
            }, replacements {}, l.Values));
        }

        machine::symbol_defs def (machine::symbol_defs defs, symbol x, type of, expression as) {
            return defs.insert (x, machine::definition {casted {of, as}},
                [x] (const machine::definition &prev, const machine::definition &next) -> machine::definition {
                    // if the definition is not a casted expression, then it's a function definition
                    // so it's not compatible with what we're saying now.
                    if (!std::holds_alternative<casted> (prev))
                        throw data::exception {} << "symbol " << x << " is already defined";

                    const casted &prev_c = std::get<casted> (prev);
                    const casted &next_c = std::get<casted> (next);

                    if (bool (prev_c.Def) && next_c.Def != nullptr && prev_c.Def != next_c.Def)
                        throw data::exception {} << "symbol " << x << " is already defined";

                    if (!(next_c.Cast >= prev_c.Cast))
                        throw data::exception {} << "symbol " << x << " is already defined";

                    if (next_c.Def == nullptr) return prev;

                    return machine::definition {casted {prev_c.Cast, next_c.Def}};
                });
        }

        // now we need to find a matching definition or add one in if it doesn't exist.
        // if we find an equal definition we can stop. If we find a subset we can stop.
        // if we find something incompatible we throw an error.
        data::stack<mtf> insert_def_into_stack (Machine m, data::exception, const data::stack<mtf>, const mtf);

        machine::symbol_defs def (Machine m, machine::symbol_defs defs, symbol x, type of, data::stack<pattern> arg, expression as) {
            return defs.insert (x, machine::definition {data::stack<mtf> {mtf {arg, casted {of, as}}}},
                [m, x] (const machine::definition &prev, const machine::definition &next) {
                    data::exception excp {};
                    excp << "symbol " << x << " is already defined";
                    // if it's not a stack then it's an incompatible definition.
                    if (!std::holds_alternative<data::stack<mtf>> (prev)) throw excp;
                    const data::stack<mtf> ps = std::get<data::stack<mtf>> (prev);
                    const data::stack<mtf> ns = std::get<data::stack<mtf>> (next);
                    return insert_def_into_stack (m, excp, ps, data::first (ns));
                });
        }

        machine::unary_defs def (Machine m, machine::unary_defs defs, unary_operand op, type of, pattern arg, expression as) {
            return defs.insert (op, data::stack<mtf> {mtf {{arg}, casted {of, as}}},
                [m, op] (const data::stack<mtf> &prev, const data::stack<mtf> &next) {
                    return insert_def_into_stack (m, data::exception {} << "op " << op << " is already defined", prev, data::first (next));
                });
        }

        machine::binary_defs def (Machine m, machine::binary_defs defs, binary_operand op, type of, pattern left, pattern right, expression as) {
            return defs.insert (op, data::stack<mtf> {mtf {{left, right}, casted {of, as}}},
                [m, op] (const data::stack<mtf> &prev, const data::stack<mtf> &next) {
                    return insert_def_into_stack (m, data::exception {} << "op " << op << " is already defined", prev, data::first (next));
                });
        }

        // we need to find a matching definition or add one in if it doesn't exist.
        // if we find an equal definition we can stop. If we find a subset we can stop
        // and insert the new definition there. If we find something incompatible we
        // throw an error.
        data::stack<mtf> insert_def_into_stack (Machine m, data::exception excp, const data::stack<mtf> old, const mtf new_def) {
            data::stack<mtf> defs = old;

            // store definitions here which we have checked
            // already and which should come before the new one.
            data::stack<mtf> back;

            const type &of = new_def.Value.Cast;
            const data::stack<pattern> args = new_def.Arguments;

            while (true) {
                if (data::empty (defs)) {
                    defs <<= new_def;
                    break;
                }

                const mtf &current = data::first (defs);
                data::stack<pattern> old_args = current.Arguments;

                if (data::size (current.Arguments) > data::size (args)) {
                    defs <<= new_def;
                    break;
                }

                if (data::size (current.Arguments) == data::size (args)) {
                    // this shouldn't really happen.
                    if (data::size (current.Arguments) == 0) throw excp;

                    data::stack<pattern> new_args = args;

                    impartial_ordering comparison = compare (m, data::first (new_args), data::first (old_args));

                    // we require that the impartial
                    while (true) {
                        if (comparison == impartial_ordering::disjoint) break;

                        new_args = data::rest (new_args);
                        old_args = data::rest (old_args);

                        if (data::empty (new_args)) break;

                        comparison = comparison && compare (m, data::first (new_args), data::first (old_args));
                    }

                    if (comparison == impartial_ordering::nonempty_complements) throw excp;

                    if (comparison == impartial_ordering::subset || comparison == impartial_ordering::disjoint) {
                        defs <<= new_def;
                        break;
                    }

                    // we have to check if one definition is nil or if both are equal.
                    if (comparison == impartial_ordering::equal) {
                        throw excp; // for now we just throw the exception!
                    }
                }

                back <<= data::first (defs);
                defs = data::rest (defs);
            }

            // put the ealier definitions back onto the stack.
            while (!data::empty (back)) {
                defs <<= data::first (back);
                back = data::rest (back);
            }

            return defs;
        }

    }

}
