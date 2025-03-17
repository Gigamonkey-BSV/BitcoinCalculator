#include <machine.hpp>
#include <value.hpp>

namespace Diophant {
    expression evaluate_round (const machine &m, const node *p);

    expression machine::evaluate (Expression e) const {
        expression last = e;
        while (true) {
            const node *p = last.get ();
            expression next = evaluate_round (*this, p);
            if (next == expression {}) return last;
            last = next;
        }
    }

    struct candidate {
        replacements Replacements;
        casted Result;
        stack<expression> Remaining;
    };

    maybe<candidate> get_candidate (const machine &m, data::ordered_list<machine::transformation> tfs, stack<expression> args) {
        while (!tfs.empty ()) {

            auto &tf = tfs.first ();

            if (tf.Arguments.size () > args.size ()) return {};

            auto match_args = data::take (args, tf.Arguments.size ());

            maybe<replacements> r = m.match (tf.Arguments, match_args);

            if (bool (r)) return {{*r, tf.Value, data::drop (args, tf.Arguments.size ())}};

            tfs = tfs.rest ();
        }

        return {};
    }

    expression evaluate_binary_operation (const machine &m, const binary_operation *b);
    expression evaluate_unary_operation (const machine &m, const unary_operation *u);

    expression evaluate_list (const machine &m, const list *ls);

    expression evaluate_symbol (const machine &m, const symbol *x) {
        const machine::definition *v = m.SymbolDefinitions.contains (*x);
        if (v == nullptr) expression {};

        if (!std::holds_alternative<casted> (*v)) return expression {};

        return std::get<casted> (*v).Expr;
    }

    expression evaluate_call (const machine &m, const call *c) {
        // first we evaluate function and args individually.
        bool changed = false;
        expression fun = m.evaluate (c->Fun);
        if (fun != expression {}) changed = true;
        else fun = c->Fun;

        data::list<expression> args;
        for (Expression old_arg : stack<expression> (c->Args)) {
            expression new_arg = m.evaluate (old_arg);
            if (new_arg != expression {}) {
                changed = true;
                args <<= new_arg;
            } else args <<= old_arg;
        }

        while (true) {
            const node *p = fun.get ();

            int min_args = 1;

            // this only happens once because any further nested calls would
            // have been flattened when the function was evaluated above.
            if (const call *cc = dynamic_cast<const call *> (c); cc != nullptr) {
                // we will skip the definitions that have as many args as
                // in the inner call or fewer, since these would
                // have already been checked.

                min_args += cc->Args.size ();
                args = cc->Args + args;
                fun = cc->Fun;
                p = fun.get ();
            }

            if (const lambda *n = dynamic_cast<const lambda *> (c); n != nullptr) {
                if (n->Args.size () > args.size ()) goto done;

                changed = true;
                stack<symbol> in = n->Args;
                replacements r;

                while (!in.empty ()) {
                    r = r.insert (data::first (in), data::first (args));
                    in = data::rest (in);
                    args = data::rest (args);
                }

                fun = m.evaluate (replace (n->Body, r));

                if (args.empty ()) return fun;
                continue;
            }

            // Note: here we simply find the first possible match. However,
            // in general we want to look for a unique match or a unique
            // match with automatic type conversions.
            if (const symbol *x = dynamic_cast<const symbol *> (c); x != nullptr) {
                const machine::definition *v = m.SymbolDefinitions.contains (*x);
                if (v == nullptr || !std::holds_alternative<data::ordered_list<machine::transformation>> (*v)) goto done;

                data::ordered_list<machine::transformation> tfs = std::get<data::ordered_list<machine::transformation>> (*v);

                while (true) {
                    if (tfs.empty ()) goto done;
                    if (tfs.first ().Arguments.size () >= min_args) break;
                    tfs = tfs.rest ();
                }

                maybe<candidate> cx = get_candidate (m, tfs, args);
                if (bool (cx)) {
                    changed = true;
                    fun = m.evaluate (replace (cx->Result.Expr, cx->Replacements));
                    args = cx->Remaining;
                    continue;
                }
            }

            done:
            return changed ? call::make (fun, args) : expression {};
        }
    }

    expression evaluate_round (const machine &m, const node *p) {
        if (p == nullptr) return expression {};

        if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr)
            return evaluate_symbol (m, x);
        if (const list *ls = dynamic_cast<const list *> (p); ls != nullptr)
            return evaluate_list (m, ls);
        if (const binary_operation *b = dynamic_cast<const binary_operation *> (p); b != nullptr)
            return evaluate_binary_operation (m, b);
        if (const unary_operation *u = dynamic_cast<const unary_operation *> (p); u != nullptr)
            return evaluate_unary_operation (m, u);
        if (const call *c = dynamic_cast<const call *> (p); c != nullptr)
            return evaluate_call (m, c);

        return expression {};
    }

    maybe<replacements> machine::match (stack<pattern> p, stack<expression> e, stack<casted> known) const {
        if (p.size () != e.size ()) return {};

        replacements r;
        while (!p.empty ()) {
            auto m = match (p.first (), e.first (), known);
            if (!bool (m)) return {};
            for (const auto &[key, value] : *m)
                if (const auto *v = r.contains (key); v != nullptr) {
                    if (*v != value) return {};
                } else r = r.insert (key, value);

                p = p.rest ();
            e = e.rest ();
        }

        return r;
    }

    maybe<replacements> machine::match (const pattern p, const expression e, stack<casted> known) const {
        const form *z = p.get ();
        const node *n = e.get ();

        using mr = maybe<replacements>;

        if (const node *q = dynamic_cast<const node *> (z); q != nullptr || z == nullptr)
            return p == pattern {e} ? mr {{}} : mr {};
        else if (const blank *b = dynamic_cast<const blank *> (z); b != nullptr)
            return b->Name != "" ? mr {{{b->Name, e}}} : mr {{}};
        else if (const typed *t = dynamic_cast<const typed *> (z); t != nullptr) {
            mr r = match (t->Pattern, e, known);
            if (!bool (r)) return {};
            auto tt = derive_type (e);
            if (!bool (tt)) return {}; // this should really be an error.
            if (t->Type >= *tt) return r;
        }

        return {};
    }

    maybe<casted> cast_symbol (const machine &, const type &T, const expression &E);
    maybe<casted> cast_call (const machine &, const type &T, const expression &E);
    maybe<casted> cast_binary_operation (const machine &, const type &T, const expression &E);
    maybe<casted> cast_unary_operation (const machine &, const type &T, const expression &E);

    // try to cast a value as a type.
    maybe<casted> machine::cast (const type &T, const expression &E) {
        const node *t = T.get ();
        const node *e = E.get ();

        if (e == nullptr) return t == nullptr ? maybe<casted> {} : maybe<casted> {{T, E}};

        if (const value *v = dynamic_cast<const value *> (e); v != nullptr) return v->cast (*this, T);
        if (const symbol *x = dynamic_cast<const symbol *> (e); x != nullptr)
            return cast_symbol (*this, T, E);
        if (const binary_operation *b = dynamic_cast<const binary_operation *> (e); b != nullptr)
            return cast_binary_operation (*this, T, E);
        if (const unary_operation *u = dynamic_cast<const unary_operation *> (e); u != nullptr)
            return cast_unary_operation (*this, T, E);
        if (const call *c = dynamic_cast<const call *> (e); c != nullptr)
            return cast_call (*this, T, E);

        return {};
    }

}
