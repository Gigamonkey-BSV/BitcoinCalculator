#include <machine.hpp>

namespace Diophant {

    expression evaluate_binary_operation (const machine &m, const binary_operation *b);
    expression evaluate_unary_operation (const machine &m, const unary_operation *u);

    expression evaluate_list (const machine &m, const list *ls);

    expression evaluate_symbol (const machine &m, const symbol *x) {
        const machine::definition *v = m.SymbolDefinitions.contains (*x);
        if (v == nullptr) expression {};

        if (!std::holds_alternative<expression> (*v)) return expression {};

        return std::get<expression> (*v);
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

            if (const symbol *x = dynamic_cast<const symbol *> (c); x != nullptr) {
                const machine::definition *v = m.SymbolDefinitions.contains (*x);
                if (v == nullptr) goto done;

                if (!std::holds_alternative<data::ordered_list<machine::transformation>> (*v)) goto done;

                data::ordered_list<machine::transformation> tfs = std::get<data::ordered_list<machine::transformation>> (*v);

                while (true) {
                    if (tfs.empty ()) goto done;
                    if (tfs.first ().Arguments.size () >= min_args) break;
                    tfs = tfs.rest ();
                }

                while (true) {
                    auto &tf = tfs.first ();

                    if (tf.Arguments.size () > args.size ()) goto done;

                    auto match_args = data::take (args, tf.Arguments.size ());

                    maybe<replacements> r = match (tf.Arguments, match_args);

                    if (bool (r)) {
                        changed = true;
                        fun = m.evaluate (replace (tf.Value, *r));
                        args = data::drop (args, tf.Arguments.size ());
                        break;
                    }

                    tfs = tfs.rest ();
                }

                continue;
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

    expression machine::evaluate (Expression e) const {
        expression last = e;
        while (true) {
            const node *p = last.get ();
            expression next = evaluate_round (*this, p);
            if (next == expression {}) return last;
            last = next;
        }
    }

}
