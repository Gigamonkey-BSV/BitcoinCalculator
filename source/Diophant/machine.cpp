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

        while (!empty (pp)) {
            r = r.Machine.evaluate (first (pp));
            pp = rest (pp);
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

        if (const symbol *p = dynamic_cast<const symbol *> (n); p != nullptr)
            return {define (*p, of, as), expression {}};

        if (const call *fx = dynamic_cast<const call *> (n); fx != nullptr) {
            expression fun;
            data::stack<data::stack<expression>> args;

            while (true) {
                fun = fx->Fun;
                args >>= fx->Args;

                const node *fn = dynamic_cast<const node *> (fun.get ());

                if (fn == nullptr) throw data::exception {} << "invalid definition";

                const symbol *z = dynamic_cast<const symbol *> (fn);

                if (z != nullptr) {
                    data::stack<pattern> drgs;

                    while (!data::empty (args)) {
                        drgs = drgs + data::stack<pattern> (reverse (first (args)));
                        args = rest (args);
                    }

                    drgs = reverse (drgs);

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

    match_result machine::match (
        data::stack<pattern> p,
        data::stack<expression> e,
        data::list<machine::autocast> conversions) const {

            if (size (p) != size (e)) return {no};

        match_result result {no};
        while (!empty (p)) {
            match_result matches = Diophant::match (*this, first (p), first (e));

            if (intuit (matches) == no) return no;
            // an unknown result indicates that computation cannot continue.
            // We keep track of an unknown result and continue trying to
            // match because we could get an unambiguous no later on.
            else if (intuit (matches) == unknown) result = unknown;
            // if we get yes, then we try to combine the replacements
            // we get from this match with replacements from previous arguments.
            else if (intuit (matches) == yes) {
                if (intuit (result) == yes) {
                    try {
                        result = *result | *matches;
                    // will be thrown if these maps have any of the same keys.
                    } catch (replacements::key_already_exists) {
                        return {no};
                    }
                } else if (intuit (result) == no) result = matches;
            }

            p = rest (p);
            e = rest (e);
        }

        return result;
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

        using candidate_result = intuit_result<candidate>;

        // here we attempt to find a single candidate among the available matches
        // to evaluate. For a typeable expression, every pattern will match either
        // no or yes. For a non-typeable expression, we may not know whether we can
        // match a pattern (because the pattern may involve a type). If we generate
        // two "yes" matches, we throw an error. Other possible results are not
        // errors. If we get zero "yes" matches we return a "no" and if we get any
        // "unknown" match we return "unknown".
        // TODO we need an option for a set of automatic replacements.
        candidate_result get_candidate (const machine &m, data::stack<mtf> tfs, data::stack<expression> args) {

            // we store a potential match here but continue searching to
            // ensure that we do not match twice.
            candidate_result matched {no};

            // we keep track of a previously matched pattern in order to
            // provide a complete error if more than one pattern is matched.
            data::stack<pattern> previously_matched_pattern;

            while (!empty (tfs)) {

                auto &tf = first (tfs);
                if (size (tf.Arguments) > size (args)) return matched;
                auto match_args = take (args, size (tf.Arguments));
                match_result r = m.match (tf.Arguments, match_args);
                if (intuit (r) == yes) {
                    if (intuit (matched) == yes)
                        throw data::exception {} << "no unique match: for args " << args << ", confused by patterns " <<
                            previously_matched_pattern << " and " << tf.Arguments;

                    previously_matched_pattern = tf.Arguments;
                    matched = candidate_result {candidate {*r, tf.Value, drop (args, size (tf.Arguments))}};
                } else if (intuit (r) == unknown)
                    return {unknown};

                tfs = rest (tfs);
            }

            return matched;
        }

        expression evaluate_list (const machine &m, const list &ls) {

            bool changed = false;
            data::stack<expression> new_ls;

            for (Expression old_arg : data::stack<expression> (ls.List)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != old_arg) changed = true;
                new_ls >>= new_arg;
            }

            return changed ? list::make (reverse (new_ls)) : expression {};
        }

        expression evaluate_struct (const machine &m, const dstruct &dst) {
            bool changed = false;
            data::stack<data::entry<symbol, expression>> new_dst;

            for (data::entry<symbol, expression> old : dst.Values) {
                data::entry<symbol, expression> new_e {old.Key, m.evaluate (old.Value)};
                if (new_e.Value != old.Value) changed = true;
                new_dst >>= new_e;
            }

            return changed ? dstruct::make (reverse (new_dst)) : expression {};
        }

        expression evaluate_symbol (const machine &m, const symbol &x) {
            const machine::definition *v = m.SymbolDefinitions.contains (x);
            if (v == nullptr) return {};

            if (!std::holds_alternative<casted> (*v)) return {};

            const casted &z = std::get<casted> (*v);

            if (!bool (z.Def)) return {};

            return z.Def;
        }

        bool evaluate_eq (const machine &m, const data::stack<mtf> *defs, const expression &left, const expression &right);
        expression evaluate_bin (const machine &m, const data::stack<mtf> *defs, data::stack<expression> body, bool show = false);

        expression evaluate_binop (const machine &m, const binop &b) {
            if (b.Operand == binary_operand::define)
                throw data::exception {} << "define operator found in expression. This is not allowed!";

            if (b.Body.size () < 2) throw data::exception {"expression is too small (should be impossible)"};

            if (b.Operand == binary_operand::apply)
                return call::make (first (b.Body), rest (b.Body));

            // evaluate function and args individually.
            bool changed = false;

            data::list<expression> body;
            for (Expression old_arg : data::stack<expression> (b.Body)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != old_arg) changed = true;
                body <<= new_arg;
            }

            if (b.Operand == binary_operand::identical) {
                bool res = true;
                while (body.size () > 1) {
                    res = res && first (body) == first (rest (body));
                    if (!res) break;
                    body = rest (body);
                }
                return boolean::make (res);
            }

            if (b.Operand == binary_operand::unidentical) {
                bool res = true;
                while (size (body) > 1) {
                    res = res && first (body) != first (rest (body));
                    if (!res) break;
                    body = rest (body);
                }
                return boolean::make (res);
            }

            if (b.Operand == binary_operand::bool_equal) {
                const data::stack<mtf> *defs = m.BinaryDefinitions.contains (binary_operand::bool_equal);

                expression left;
                while (true) {
                    left = first (body);
                    body = rest (body);
                    if (size (body) == 0) return boolean::make (true);
                    if (!evaluate_eq (m, defs, left, first (body))) return boolean::make (false);
                }
            }

            if (b.Operand == binary_operand::bool_unequal) {
                const data::stack<mtf> *defs = m.BinaryDefinitions.contains (binary_operand::bool_equal);

                data::list<expression> new_body;
                expression left;
                while (true) {
                    left = first (body);
                    body = rest (body);
                    if (size (body) == 0) return boolean::make (true);
                    if (evaluate_eq (m, defs, left, first (body))) return boolean::make (false);
                }
            }

            expression result;

            if (b.Operand == binary_operand::dot) {
                while (true) {
                    if (body.size () == 1) return first (body);

                    auto fst = first (body);
                    auto snd = first (rest (body));
                    if (const dstruct *ds = dynamic_cast<const dstruct *> (fst.get ()); ds != nullptr) {
                        if (const symbol *x = dynamic_cast<const symbol *> (snd.get ()); x != nullptr)
                            for (const auto &[name, val] : ds->Values)
                                if (*x == name) {
                                    changed = true;
                                    body = data::prepend (data::drop (body, 2), m.evaluate (val));
                                    goto continue_evaluate_dot;
                                }
                    } else if (const list *ls = dynamic_cast<const list *> (fst.get ()); ls != nullptr) {
                        if (const natural *x = dynamic_cast<const natural *> (snd.get ()); x != nullptr) {
                            changed = true;
                            body = data::prepend (data::drop (body, 2), m.evaluate (ls->List[size_t (x->Value)]));
                            continue;
                        }
                    }

                    break;
                    continue_evaluate_dot:
                }

            }

            // NOTE technically we could have elements
            // leftover and we'd have to go back and keep trying.
            result = evaluate_bin (m, m.BinaryDefinitions.contains (b.Operand), body, true);

            return bool (result) ? result : changed ? binop::make (b.Operand, body) : expression {};
        }

        expression evaluate_bin (const machine &m, const data::stack<mtf> *defs, data::stack<expression> body, bool show) {
            if (defs == nullptr) return expression {};

            data::stack<mtf> tfs = *defs;

            candidate_result cx = get_candidate (m, tfs, body);
            if (intuit (cx) == yes) {
                if (cx->Result.Def == expression {})
                    throw data::exception {} << "Error: attempt to evaluate undefined pattern";

                    return replace (cx->Result.Def, cx->Replacements);
            }

            // we can try again with automatic conversions.
            if (intuit (cx) == no) {

            }

            return expression {};
        }

        bool evaluate_eq (const machine &m, const data::stack<mtf> *defs, const expression &left, const expression &right) {

            expression result = evaluate_bin (m, defs, {left, right});
            if (!result) return left == right;

            if (const boolean *b = dynamic_cast<const boolean *> (m.evaluate (result).get ()); b != nullptr) {
                return b->Value;
            } else throw data::exception {} << "operator == must return bool";
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
                candidate_result cx = get_candidate (m, tfs, {body});

                if (intuit (cx) == yes) {
                    changed = true;
                    if (!bool (cx->Result.Def))
                        throw data::exception {} << "Error: attempt to evaluate undefined pattern";

                    auto replaced = replace (cx->Result.Def, cx->Replacements);
                    return m.evaluate (replaced);
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
                    args = reverse (args + reverse (fx->Args));
                    fun = fx->Fun;
                    p = fun.get ();
                    changed = true;
                }

                // if the head is a lambda, we can evaluate it completely lazily.
                if (const lambda *n = dynamic_cast<const lambda *> (p); n != nullptr) {
                    if (size (n->Args) > size (args)) break;

                    changed = true;
                    data::stack<symbol> in = n->Args;
                    replacements r;

                    while (!data::empty (in)) {
                        r = r.insert (first (in), first (args));
                        in = rest (in);
                        args = rest (args);
                    }

                    fun = m.evaluate (replace (n->Body, r));
                    if (empty (args)) return fun;
                    continue;
                }

                if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr) {
                    // look for definitions corresponding to this symbol.
                    const machine::definition *v = m.SymbolDefinitions.contains (*x);
                    if (v == nullptr || !std::holds_alternative<data::stack<mtf>> (*v)) break;

                    data::stack<mtf> tfs = std::get<data::stack<mtf>> (*v);
                    while (true) {
                        if (empty (tfs)) goto done;
                        if (size (first (tfs).Arguments) >= min_args) break;
                        tfs = rest (tfs);
                    }

                    candidate_result cx = get_candidate (m, tfs, args);
                    if (intuit (cx) == yes) {
                        changed = true;
                        if (!bool (cx->Result.Def))
                            throw data::exception {} << "Error: attempt to evaluate undefined pattern";
                        fun = m.evaluate (replace (cx->Result.Def, cx->Replacements));
                        args = cx->Remaining;
                        if (args.size () == 0) return fun;
                        continue;
                    };

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
                            new_args >>= next;
                        }
                        if (changed) args = reverse (new_args);
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
                new_args >>= next;
                if (next != ex) changed = true;
            }

            args = reverse (new_args);

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

                const bytes *x = dynamic_cast<const bytes *> (first (fx->Args).get ());
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
                [m, x, arg] (const machine::definition &prev, const machine::definition &next) {
                    data::exception excp {};
                    excp << "symbol " << x << " is already defined for args " << arg;
                    // if it's not a stack then it's an incompatible definition.
                    if (!std::holds_alternative<data::stack<mtf>> (prev)) throw excp;
                    const data::stack<mtf> ps = std::get<data::stack<mtf>> (prev);
                    const data::stack<mtf> ns = std::get<data::stack<mtf>> (next);
                    return insert_def_into_stack (m, excp, ps, first (ns));
                });
        }

        machine::unary_defs def (Machine m, machine::unary_defs defs, unary_operand op, type of, pattern arg, expression as) {
            return defs.insert (op, data::stack<mtf> {mtf {{arg}, casted {of, as}}},
                [m, op] (const data::stack<mtf> &prev, const data::stack<mtf> &next) {
                    return insert_def_into_stack (m, data::exception {} << "op " << op << " is already defined", prev, first (next));
                });
        }

        machine::binary_defs def (Machine m, machine::binary_defs defs, binary_operand op, type of, pattern left, pattern right, expression as) {
            return defs.insert (op, data::stack<mtf> {mtf {{left, right}, casted {of, as}}},
                [m, op, left, right] (const data::stack<mtf> &prev, const data::stack<mtf> &next) {
                    return insert_def_into_stack (m, data::exception {} << "op " << op << " is already defined for " << left << " and " << right, prev, first (next));
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

            // the return type
            const type &of = new_def.Value.Cast;

            // the arguments.
            const data::stack<pattern> args = new_def.Arguments;

            while (true) {
                if (empty (defs)) {
                    defs >>= new_def;
                    break;
                }

                const mtf &current = first (defs);
                data::stack<pattern> old_args = current.Arguments;

                if (size (current.Arguments) > data::size (args)) {
                    defs >>= new_def;
                    break;
                }

                if (data::size (current.Arguments) == data::size (args)) {
                    // this shouldn't really happen.
                    if (data::size (current.Arguments) == 0) throw excp;

                    data::stack<pattern> new_args = args;

                    // The whole set of patterns does not naturally satisfy an ordering relation.
                    // We require that all patterns defined for a symbol be partially orderable
                    // by the subset relation. Thus, they must either be equal, be sub- or supersets
                    // of each other, or be disjoint.
                    impartial_ordering comparison {impartial_ordering::equal};

                    while (true) {
                        comparison = comparison && compare (m, first (new_args), first (old_args));

                        if (comparison == impartial_ordering::disjoint) break;

                        new_args = data::rest (new_args);
                        old_args = data::rest (old_args);

                        if (data::empty (new_args)) break;
                    }

                    if (comparison == impartial_ordering::nonempty_complements) throw excp;

                    if (comparison == impartial_ordering::subset || comparison == impartial_ordering::disjoint) {
                        defs >>= new_def;
                        break;
                    }

                    // we have to check if one definition is nil or if both are equal.
                    if (comparison == impartial_ordering::equal)
                        throw excp; // for now we just throw the exception!
                }

                back >>= first (defs);
                defs = rest (defs);
            }

            // put the ealier definitions back onto the stack.
            while (!empty (back)) {
                defs >>= first (back);
                back = rest (back);
            }

            return defs;
        }

    }

}
