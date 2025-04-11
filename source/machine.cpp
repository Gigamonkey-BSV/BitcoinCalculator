#include <machine.hpp>
#include <values/list.hpp>
#include <values/lambda.hpp>
#include <values/struct.hpp>
#include <values/leaf.hpp>
#include <data/io/wait_for_enter.hpp>

namespace Diophant {
    namespace {
        machine::symbol_defs def (machine::symbol_defs, symbol x, type of, expression as);
        machine::symbol_defs def (machine::symbol_defs, symbol x, type of, data::stack<pattern> arg, expression as);
        machine::unary_defs def (machine::unary_defs, unary_operand op, type of, pattern arg, expression as);
        machine::binary_defs def (machine::binary_defs, binary_operand op, type of, pattern left, pattern right, expression as);
    }

    machine machine::define (symbol x, expression as) const {
        return machine {def (SymbolDefinitions, x, type {}, as), UnaryDefinitions, BinaryDefinitions};
    }

    machine machine::define (symbol x, data::stack<pattern> arg, expression as) const {
        return machine {def (SymbolDefinitions, x, type {}, arg, as), UnaryDefinitions, BinaryDefinitions};
    }

    machine machine::define (symbol x, type of, expression as) const {
        return machine {def (SymbolDefinitions, x, of, as), UnaryDefinitions, BinaryDefinitions};
    }

    machine machine::define (symbol x, type of, data::stack<pattern> arg, expression as) const {
        return machine {def (SymbolDefinitions, x, of, arg, as), UnaryDefinitions, BinaryDefinitions};
    }

    machine machine::define (unary_operand op, pattern in, expression as) const {
        return machine {SymbolDefinitions, def (UnaryDefinitions, op, type {}, in, as), BinaryDefinitions};
    }

    machine machine::define (binary_operand op, pattern left, pattern right, expression as) const {
        return machine {SymbolDefinitions, UnaryDefinitions, def (BinaryDefinitions, op, type {}, left, right, as)};
    }

    machine machine::define (unary_operand op, type of, pattern in, expression as) const {
        return machine {SymbolDefinitions, def (UnaryDefinitions, op, of, in, as), BinaryDefinitions};
    }

    machine machine::define (binary_operand op, type of, pattern left, pattern right, expression as) const {
        return machine {SymbolDefinitions, UnaryDefinitions, def (BinaryDefinitions, op, of, left, right, as)};
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

            if (bool (n->Evaluated)) return last;

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

    data::maybe<replacements> machine::match (data::stack<pattern> p, data::stack<expression> e) const {
        if (data::size (p) != data::size (e)) return {};

        replacements r;
        while (!data::empty (p)) {
            auto m = match (data::first (p), data::first (e));
            if (!bool (m)) return {};
            try {
                r = r & *m;
            // will be thrown if these maps have any of the same keys.
            } catch (replacements::key_already_exists) {
                return {};
            }

            p = data::rest (p);
            e = data::rest (e);
        }
        return r;
    }

    data::maybe<replacements> machine::match (const pattern patt, const expression expr) const {
        const form *z = patt.get ();
        const form *n = expr.get ();

        using mr = data::maybe<replacements>;

        if (z == n || z == nullptr) return mr {{}};

        if (const blank *b = dynamic_cast<const blank *> (z); b != nullptr) {
            return b->Name != "" ? mr {replacements {{b->Name, expr}}} : mr {replacements {}};
        }

        if (const typed *t = dynamic_cast<const typed *> (z); t != nullptr) {
            mr r = match (t->Match, expr);
            if (!bool (r)) return {};
            if (cast (t->Required, expr)) return r;
        }

        if (const symbol *x = dynamic_cast<const symbol *> (z); x != nullptr) {
            const symbol *y = dynamic_cast<const symbol *> (n);
            if (y == nullptr) return {};
            return *x == *y ? mr {replacements {}} : mr {};
        }

        if (const unop *u = dynamic_cast<const unop *> (z); u != nullptr) {
            const unop *v = dynamic_cast<const unop *> (n);
            if (v == nullptr || v->Operand != u->Operand) return {};
            return match (u->Body, v->Body);
        }

        if (const binop *b = dynamic_cast<const binop *> (z); b != nullptr) {
            const binop *c = dynamic_cast<const binop *> (n);
            if (c == nullptr || b->Operand != c->Operand) return {};
            return match (data::stack<expression> (b->Body), data::stack<expression> (c->Body));
        }

        if (const call *fx = dynamic_cast<const call *> (z); fx != nullptr) {
            const call *gx = dynamic_cast<const call *> (n);
            if (gx == nullptr) return {};
            auto rf = match (fx->Fun, gx->Fun);
            if (!bool (rf)) return {};
            auto rx = match (data::stack<pattern> (data::stack<expression> (fx->Args)), data::stack<expression> (gx->Args));
            if (!bool (rx)) return {};
            try {
                return *rf & *rx;
            // will be thrown if these maps have any of the same keys.
            } catch (replacements::key_already_exists) {
                return {};
            }
        }

        if (const list *jk = dynamic_cast<const list *> (z); jk != nullptr) {
            const list *mn = dynamic_cast<const list *> (n);
            if (mn == nullptr || jk->List.size () != mn->List.size ()) return {};

            replacements m {};
            auto jkl = jk->List;
            auto mno = mn->List;
            while (!data::empty (jkl)) {
                auto r = match (data::first (jkl), data::first (mno));
                if (!bool (r)) return {};
                jkl = data::rest (jkl);
                mno = data::rest (mno);
                try {
                    m = m & *r;
                    // will be thrown if these maps have any of the same keys.
                } catch (replacements::key_already_exists) {
                    return {};
                }
            }
            return m;
        }

        if (const value *v = dynamic_cast<const value *> (z); v != nullptr) {
            const value *q = dynamic_cast<const value *> (n);
            if (q == nullptr) return {};
            return *v == *q ? mr {replacements {}} : mr {};
        }

        return {};
    }

    namespace {
        bool cast_symbol (const machine &, const form *t, const symbol *x);
        bool cast_call (const machine &, const form *t, const call *c);
        bool cast_binop (const machine &, const form *t, const expression &E);
        bool cast_unop (const machine &, const form *t, const expression &E);
    }

    // try to cast a value as a type.
    bool machine::cast (Type T, Expression E) const {
        const form *t = T.get ();
        const form *e = E.get ();

        if (e == nullptr) return t == nullptr;

        if (const value *v = dynamic_cast<const value *> (e); v != nullptr)
            return v->cast (*this, T);
        if (const symbol *x = dynamic_cast<const symbol *> (e); x != nullptr)
            return cast_symbol (*this, t, x);
        if (const binop *b = dynamic_cast<const binop *> (e); b != nullptr)
            return cast_binop (*this, t, E);
        if (const unop *u = dynamic_cast<const unop *> (e); u != nullptr)
            return cast_unop (*this, t, E);
        if (const call *c = dynamic_cast<const call *> (e); c != nullptr)
            return cast_call (*this, t, c);

        return false;
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
            data::maybe<candidate> matched {};
            while (!data::empty (tfs)) {

                auto &tf = data::first (tfs);

                if (data::size (tf.Arguments) > data::size (args)) return {};

                auto match_args = data::take (args, data::size (tf.Arguments));
                data::maybe<replacements> r = m.match (tf.Arguments, match_args);

                if (bool (r)) {
                    if (bool (matched)) throw data::exception {} << "no unique match";
                    matched = {{*r, tf.Value, data::drop (args, data::size (tf.Arguments))}};
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

            data::list<expression> body;
            for (Expression old_arg : data::stack<expression> (b.Body)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != old_arg) changed = true;
                body <<= new_arg;
            }

            if (body.size () < 2) throw data::exception {"apply expression is too small (should be impossible)"};

            if (b.Operand == binary_operand::apply)
                return call::make (first (body), rest (body));

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

        expression evaluate_call (const machine &m, const call &c) {
            // first we evaluate function and args individually.
            bool changed = false;
            expression fun = m.evaluate (c.Fun);
            if (fun != c.Fun) changed = true;

            data::list<expression> args;
            for (Expression old_arg : data::stack<expression> (c.Args)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != old_arg) changed = true;
                args <<= new_arg;
            }

            // next we try to match the function and args against our definitions.
            while (true) {
                const form *p = fun.get ();

                if (p == nullptr) break;

                int min_args = 1;

                // this only happens once because any further nested calls would
                // have been flattened when the function was evaluated above.
                if (const call *fx = dynamic_cast<const call *> (p); fx != nullptr) {
                    // we will skip the definitions that have as many args as
                    // in the inner call or fewer, since these would
                    // have already been checked.

                    min_args += data::size (fx->Args);
                    args = fx->Args + args;
                    fun = fx->Fun;
                    p = fun.get ();
                }

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

                // Note: here we simply find the first possible match. However,
                // in general we want to look for a unique match or a unique
                // match with automatic type conversions.
                if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr) {
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
                }

                if (const value *v = dynamic_cast<const value *> (p); v != nullptr) {
                    expression next = (*v) (args);
                    if (next == expression {}) break;
                    return next;
                }

                break;
            }

            done:
            return changed ? call::make (fun, args) : expression {};
        }

        expression evaluate_if (const machine &m, const dif &df) {
            auto If = m.evaluate (df.If);
            if (const scriptnum *xx = dynamic_cast<const scriptnum *> (If.get ()); xx != nullptr)
                return Bitcoin::nonzero (xx->Value) ? df.Then : df.Else;
            else return {};
        }

        expression evaluate_let (const machine &m, const let &l) {
            return replace (l.In, data::fold ([] (auto &&r, auto &&v) {
                return r.insert (v);
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
        data::stack<mtf> insert_def_into_stack (data::exception, const data::stack<mtf>, const mtf);

        machine::symbol_defs def (machine::symbol_defs defs, symbol x, type of, data::stack<pattern> arg, expression as) {
            return defs.insert (x, machine::definition {data::stack<mtf> {mtf {arg, casted {of, as}}}},
                [x] (const machine::definition &prev, const machine::definition &next) {
                    data::exception excp {};
                    excp << "symbol " << x << " is already defined D";
                    // if it's not a stack then it's an incompatible definition.
                    if (!std::holds_alternative<data::stack<mtf>> (prev)) throw excp;
                    const data::stack<mtf> ps = std::get<data::stack<mtf>> (prev);
                    const data::stack<mtf> ns = std::get<data::stack<mtf>> (next);
                    return insert_def_into_stack (excp, ps, data::first (ns));
                });
        }

        machine::unary_defs def (machine::unary_defs defs, unary_operand op, type of, pattern arg, expression as) {
            return defs.insert (op, data::stack<mtf> {mtf {{arg}, casted {of, as}}},
                [op] (const data::stack<mtf> &prev, const data::stack<mtf> &next) {
                    return insert_def_into_stack (data::exception {} << "op " << op << " is already defined", prev, data::first (next));
                });
        }

        machine::binary_defs def (machine::binary_defs defs, binary_operand op, type of, pattern left, pattern right, expression as) {
            return defs.insert (op, data::stack<mtf> {mtf {{left, right}, casted {of, as}}},
                [op] (const data::stack<mtf> &prev, const data::stack<mtf> &next) {
                    return insert_def_into_stack (data::exception {} << "op " << op << " is already defined", prev, data::first (next));
                });
        }

        bool cast_symbol (const machine &, const form *t, const symbol *x) {
            const symbol *cx = dynamic_cast<const symbol *> (t);
            if (x == nullptr) return false;
            return *cx == *x;
        }

        bool cast_call (const machine &m, const form *t, const call *c) {
            const call *ct = dynamic_cast<const call *> (t);
            if (ct == nullptr) return false;

            auto targ = ct->Args;
            auto carg = c->Args;
            if (data::size (targ) != data::size (carg)) return false;

            while (data::size (targ) > 0) {
                if (!m.cast (targ.first (), carg.first ())) return false;
                targ = data::rest (targ);
                carg = data::rest (carg);
            }

            return m.cast (ct->Fun, c->Fun);
        }

        bool cast_binop (const machine &, const form *t, const expression &E) {
            throw data::exception {} << "cast_binop: ";
        }

        bool cast_unop (const machine &, const form *t, const expression &E) {
            throw data::exception {} << "cast_unop: ";
        }

        // we need to find a matching definition or add one in if it doesn't exist.
        // if we find an equal definition we can stop. If we find a subset we can stop.
        // if we find something incompatible we throw an error.
        data::stack<mtf> insert_def_into_stack (data::exception excp, const data::stack<mtf> old, const mtf new_def) {
            data::stack<mtf> z = old;
            data::stack<mtf> back;

            const type &of = new_def.Value.Cast;
            const data::stack<pattern> args = new_def.Arguments;

            while (true) {
                if (data::empty (z)) {
                    z <<= new_def;
                    break;
                }

                const mtf &current = data::first (z);
                data::stack<pattern> old_args = current.Arguments;

                if (data::size (current.Arguments) > data::size (args)) {
                    z <<= new_def;
                    break;
                }

                if (data::size (current.Arguments) == data::size (args)) {
                    // this shouldn't really happen.
                    if (data::size (current.Arguments) == 0) throw excp;

                    data::stack<pattern> new_args = args;

                    impartial_ordering comparison = data::first (new_args) <=> data::first (old_args);

                    // we require that the impartial
                    while (true) {
                        if (comparison == impartial_ordering::disjoint) break;

                        new_args = data::rest (new_args);
                        old_args = data::rest (old_args);

                        if (data::empty (new_args)) break;

                        comparison = comparison && (data::first (new_args) <=> data::first (old_args));
                    }

                    if (comparison == impartial_ordering::nonempty_complements) throw excp;

                    if (comparison == impartial_ordering::subset || comparison == impartial_ordering::disjoint) {
                        z <<= new_def;
                        break;
                    }

                    // we have to check if one definition is nil or if both are equal.
                    if (comparison == impartial_ordering::equal) {
                        throw excp; // for now we just throw the exception!
                    }
                }

                back <<= data::first (z);
                z = data::rest (z);
            }

            while (!data::empty (back)) {
                z <<= data::first (back);
                back = data::rest (back);
            }

            return z;
        }

    }

}
