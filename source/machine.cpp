#include <machine.hpp>
#include <values/list.hpp>
#include <values/lambda.hpp>
#include <data/io/wait_for_enter.hpp>

namespace Diophant {

    namespace {

        expression &decl (machine &m, symbol x, type of);
        expression &decl (machine &m, symbol x, type of, data::stack<pattern> arg);
        expression &decl (machine &m, unary_operand op, type of, pattern in);
        expression &decl (machine &m, binary_operand op, type of, pattern left, pattern right);

    }

    machine machine::declare (symbol x) const {
        machine m = *this;
        decl (m, x, type {});
        return m;
    }

    machine machine::declare (symbol x, data::stack<pattern> arg) const {
        machine m = *this;
        decl (m, x, type {}, arg);
        return m;
    }

    machine machine::declare (unary_operand op, pattern in) const {
        machine m = *this;
        decl (m, op, type {}, in);
        return m;
    }

    machine machine::declare (binary_operand op, pattern left, pattern right) const {
        machine m = *this;
        decl (m, op, type {}, left, right);
        return m;
    }

    machine machine::declare (symbol x, type of) const {
        machine m = *this;
        decl (m, x, of);
        return m;
    }

    machine machine::declare (symbol x, type of, data::stack<pattern> arg) const {
        machine m = *this;
        decl (m, x, of, arg);
        return m;
    }

    machine machine::declare (unary_operand op, type of, pattern in) const {
        machine m = *this;
        decl (m, op, of, in);
        return m;
    }

    machine machine::declare (binary_operand op, type of, pattern left, pattern right) const {
        machine m = *this;
        decl (m, op, of, left, right);
        return m;
    }

    machine machine::define (symbol x, expression as) const {
        machine m = *this;
        expression &def = decl (m, x, type {});
        if (!bool (def)) def = as;
        else if (def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (symbol x, data::stack<pattern> arg, expression as) const {
        machine m = *this;
        expression &def = decl (m, x, type {}, arg);
        if (!bool (def)) def = as;
        else if (def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (unary_operand op, pattern in, expression as) const {
        machine m = *this;
        expression &def = decl (m, op, type {}, in);
        if (!bool (def)) def = as;
        else if (def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (binary_operand op, pattern left, pattern right, expression as) const {
        machine m = *this;
        expression &def = decl (m, op, type {}, left, right);
        if (!bool (def)) def = as;
        else if (def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (symbol x, type of, expression as) const {
        machine m = *this;
        expression &def = decl (m, x, of);
        if (!bool (def)) def = as;
        else if (def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (symbol x, type of, data::stack<pattern> arg, expression as) const {
        machine m = *this;
        expression &def = decl (m, x, of, arg);
        if (!bool (def)) def = as;
        else if (def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (unary_operand op, type of, pattern in, expression as) const {
        machine m = *this;
        expression &def = decl (m, op, of, in);
        if (!bool (def)) def = as;
        else if (def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (binary_operand op, type of, pattern left, pattern right, expression as) const {
        machine m = *this;
        expression &def = decl (m, op, of, left, right);
        if (!bool (def)) def = as;
        else if (def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    namespace {

        expression evaluate_round (const machine &m, Expression e);

        // indicates that an expression has been checked already so we don't need to again.
        struct checked : form {
            expression Expr;
        };

    }

    // note: this algorithm results in attempts to evaluate
    // sub expressions over again that have not changed.
    // We might want to mark expressions as already having been
    // evaluated.
    expression machine::evaluate (Expression e) const {

        expression last = e;
        while (true) {
            expression next = evaluate_round (*this, last);
            if (!bool (next) || next.get () == last.get ())
                return last;

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
                r = r + *m;
            // will be thrown if these maps have any of the same keys.
            } catch (data::exception xxx) {
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

        if (const symbol *x = dynamic_cast<const symbol *> (z); x != nullptr) {
            const symbol *y = dynamic_cast<const symbol *> (n);
            if (y == nullptr) return {};
            return *x == *y ? mr {replacements {}} : mr {};
        }

        if (const value *v = dynamic_cast<const value *> (z); v != nullptr) {
            const value *q = dynamic_cast<const value *> (n);
            if (q == nullptr) return {};
            return *v == *q ? mr {replacements {}} : mr {};
        }

        if (const blank *b = dynamic_cast<const blank *> (z); b != nullptr) {
            return b->Name != "" ? mr {{{b->Name, expr}}} : mr {replacements {}};
        }

        if (const typed *t = dynamic_cast<const typed *> (z); t != nullptr) {
            mr r = match (t->Match, expr);
            if (!bool (r)) return {};
            if (cast (t->Required, expr)) return r;
        }

        if (const unary_operation *u = dynamic_cast<const unary_operation *> (z); u != nullptr) {
            const unary_operation *v = dynamic_cast<const unary_operation *> (n);
            if (v == nullptr || v->Operator != u->Operator) return {};
            return match (u->Body, v->Body);
        }

        if (const binary_operation *b = dynamic_cast<const binary_operation *> (z); b != nullptr) {
            const binary_operation *c = dynamic_cast<const binary_operation *> (n);
            if (c == nullptr || b->Operator != c->Operator) return {};
            return match (b->Body, c->Body);
        }

        if (const call *fx = dynamic_cast<const call *> (z); fx != nullptr) {
            const call *gx = dynamic_cast<const call *> (n);
            if (gx == nullptr) return {};
            auto rf = match (fx->Fun, gx->Fun);
            if (!bool (rf)) return {};
            auto rx = match (data::stack<pattern> (data::stack<expression> (fx->Args)), data::stack<expression> (gx->Args));
            if (!bool (rx)) return {};
            return *rf + *rx;
        }

        return {};
    }

    namespace {
        bool cast_symbol (const machine &, const form *t, const symbol *x);
        bool cast_call (const machine &, const form *t, const call *c);
        bool cast_binary_operation (const machine &, const form *t, const expression &E);
        bool cast_unary_operation (const machine &, const form *t, const expression &E);
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
        if (const binary_operation *b = dynamic_cast<const binary_operation *> (e); b != nullptr)
            return cast_binary_operation (*this, t, E);
        if (const unary_operation *u = dynamic_cast<const unary_operation *> (e); u != nullptr)
            return cast_unary_operation (*this, t, E);
        if (const call *c = dynamic_cast<const call *> (e); c != nullptr)
            return cast_call (*this, t, c);

        return false;
    }

    namespace {

        expression evaluate_list (const machine &m, const list &ls);

        expression evaluate_symbol (const machine &m, const symbol &x);

        expression evaluate_binary_operation (const machine &m, const binary_operation &b);

        expression evaluate_unary_operation (const machine &m, const unary_operation &u);

        expression evaluate_call (const machine &m, const call &c);

        expression evaluate_round (const machine &m, Expression e) {
            const form *p = e.get ();
            if (p == nullptr) return e;

            if (const checked *c = dynamic_cast<const checked *> (p); c != nullptr) return {};
            if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr)
                return evaluate_symbol (m, *x);
            if (const list *ls = dynamic_cast<const list *> (p); ls != nullptr)
                return evaluate_list (m, *ls);
            if (const binary_operation *b = dynamic_cast<const binary_operation *> (p); b != nullptr)
                return evaluate_binary_operation (m, *b);
            if (const unary_operation *u = dynamic_cast<const unary_operation *> (p); u != nullptr)
                return evaluate_unary_operation (m, *u);
            if (const call *fx = dynamic_cast<const call *> (p); fx != nullptr)
                return evaluate_call (m, *fx);
            if (const value *v = dynamic_cast<const value *> (p); v != nullptr) return e;

            throw data::exception {} << "Unknown expression";
        }

        using mtf = machine::transformation;

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

            data::list<expression> new_ls;
            for (Expression old_arg : data::stack<expression> (ls.List)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != old_arg) changed = true;
            }

            return changed ? list::make (new_ls) : expression {};
        }

        expression evaluate_symbol (const machine &m, const symbol &x) {

            const machine::definition *v = m.SymbolDefinitions.contains (x);
            if (v == nullptr) return {};

            if (!std::holds_alternative<casted> (*v)) return {};

            const casted &z = std::get<casted> (*v);

            if (!bool (z.Def)) return {};

            return z.Def;
        }

        expression evaluate_binary_operation (const machine &m, const binary_operation &b) {
            // first we evaluate function and args individually.
            bool changed = false;

            data::list<expression> body;
            for (Expression old_arg : data::stack<expression> (b.Body)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != old_arg) changed = true;
                body <<= new_arg;
            }

            if (const data::stack<mtf> *v = m.BinaryDefinitions.contains (b.Operator); v != nullptr) {

                data::stack<mtf> tfs = *v;

                if (data::maybe<candidate> cx = get_candidate (m, tfs, body); bool (cx)) {
                    changed = true;
                    if (!bool (cx->Result.Def))
                        throw data::exception {} << "Error: attempt to evaluate undefined pattern";
                    return m.evaluate (replace (cx->Result.Def, cx->Replacements));
                }
            }

            return changed ? binary_operation::make (b.Operator, body) : expression {};
        }

        expression evaluate_unary_operation (const machine &m, const unary_operation &u) {
            // first we evaluate function and args individually.
            bool changed = false;
            expression body = m.evaluate (u.Body);
            if (body != u.Body) changed = true;

            {
                const data::stack<mtf> *v = m.UnaryDefinitions.contains (u.Operator);
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
            return changed ? unary_operation::make (u.Operator, body) : expression {};
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
                    if (! bool (next)) break;
                    return next;
                }

                break;
            }

            done:
            return changed ? call::make (fun, args) : expression {};
        }

        expression &decl (machine &m, symbol x, type of) {
            auto *v = m.SymbolDefinitions.contains (x);

            if (v == nullptr) {
                m.SymbolDefinitions = m.SymbolDefinitions.insert (x, casted {of});
                v = m.SymbolDefinitions.contains (x);
                return std::get<casted> (*v).Def;
            }

            if (!std::holds_alternative<casted> (*v))
                throw data::exception {} << "incompatible definitions already provided for " << x;

            casted &z = std::get<casted> (*v);

            if (bool (std::get<casted> (*v).Def))
                throw data::exception {} << "symbol " << x << " is already defined";

            return z.Def;
        }

        // now we need to find a matching definition or add one in if it doesn't exist.
        // if we find an equal definition we can stop. If we find a subset we can stop.
        // if we find something incompatible we throw an error.
        expression &insert_declaration_into_stack (data::stack<mtf> &z, type of, data::stack<pattern> arg);

        expression &decl (machine &m, symbol x, type of, data::stack<pattern> arg) {
            auto *v = m.SymbolDefinitions.contains (x);

            if (v == nullptr) {
                m.SymbolDefinitions =
                    m.SymbolDefinitions.insert (x,
                        data::stack<mtf> {mtf {arg, casted {of}}});
                v = m.SymbolDefinitions.contains (x);
                return std::get<data::stack<mtf>> (*v).first ().Value.Def;
            }

            if (!std::holds_alternative<data::stack<mtf>> (*v))
                throw data::exception {} << "symbol " << x << " is already defined";

            return insert_declaration_into_stack (std::get<data::stack<mtf>> (*v), of, arg);
        }

        expression &decl (machine &m, unary_operand op, type of, pattern in) {
            data::stack<mtf> *v = m.UnaryDefinitions.contains (op);

            if (v == nullptr) {
                m.UnaryDefinitions = m.UnaryDefinitions.insert (op, {machine::transformation {{in}, casted {of}}});
                v = m.UnaryDefinitions.contains (op);
                return v->first ().Value.Def;
            }

            return insert_declaration_into_stack (*v, of, {in});
        }

        expression &decl (machine &m, binary_operand op, type of, pattern left, pattern right) {
            data::stack<mtf> *v = m.BinaryDefinitions.contains (op);

            if (v == nullptr) {
                m.BinaryDefinitions = m.BinaryDefinitions.insert (op, {machine::transformation {{left, right}, casted {of}}});
                v = m.BinaryDefinitions.contains (op);
                return v->first ().Value.Def;
            }

            return insert_declaration_into_stack (*v, of, {left, right});
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

        bool cast_binary_operation (const machine &, const form *t, const expression &E) {
            throw data::exception {} << "cast_binary_operation: ";
        }

        bool cast_unary_operation (const machine &, const form *t, const expression &E) {
            throw data::exception {} << "cast_unary_operation: ";
        }

        // we need to find a matching definition or add one in if it doesn't exist.
        // if we find an equal definition we can stop. If we find a subset we can stop.
        // if we find something incompatible we throw an error.
        expression &insert_declaration_into_stack (data::stack<mtf> &z, type of, data::stack<pattern> arg) {
            data::stack<mtf> back;

            while (true) {
                if (data::empty (z)) {
                    z <<= mtf {arg, casted {of}};
                    break;
                }

                // TODO: we have to do more to handle overloads here.

                back <<= data::first (z);
                z = data::rest (z);
            }

            expression &val = z.first ().Value.Def;

            while (!data::empty (back)) {
                z <<= data::first (back);
                back = data::rest (back);
            }

            return val;
        }

    }

}
