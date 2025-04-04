#include <replace.hpp>
#include <values/list.hpp>
#include <values/lambda.hpp>

namespace Diophant {

    // return null if no replacement is made.
    expression replace_inner (Expression e, replacements rr) {
        const form *p = e.get ();
        if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr) {
            const auto *r = rr.contains (*x);
            return r != nullptr ? *r : expression {};
        } else if (const lambda *q = dynamic_cast<const lambda *> (p); q != nullptr) {
            // if the variables in the lambda expression contain
            // any of the replacement symbols, they are removed
            // from the replacements.
            data::stack<symbol> removed;
            for (const symbol &x : q->Args) if (data::contains (rr, x)) removed <<= x;
            for (const symbol &x : removed) rr = data::remove (rr, x);

            if (expression replaced = replace_inner (q->Body, rr); replaced != nullptr)
                return lambda::make (q->Args, replaced);
            else return expression {};
        } else if (const list *ls = dynamic_cast<const list *> (p); ls != nullptr) {
            bool replacement_was_made = false;
            data::stack<expression> new_list;

            for (const expression z : ls->List) {
                expression replaced = replace_inner (z, rr);
                if (replaced != expression {}) {
                    new_list <<= replaced;
                } else new_list <<= z;
            }

            return replacement_was_made ? list::make (data::reverse (new_list)): expression {};
        } else if (const binary_operation *b = dynamic_cast<const binary_operation *> (p); b != nullptr) {
            bool replacement_was_made = false;
            data::stack<expression> new_list;

            for (Expression z : b->Body) {
                expression replaced = replace_inner (z, rr);
                if (replaced != expression {}) {
                    replacement_was_made = true;
                    new_list <<= replaced;
                } else new_list <<= z;
            }

            if (!replacement_was_made) return expression {};
            return binary_operation::make (b->Operator, new_list);
        } if (const unary_operation *u = dynamic_cast<const unary_operation *> (p); u != nullptr) {
            expression replaced = replace_inner (u->Body, rr);
            return replaced == expression {} ? expression {} : unary_operation::make (u->Operator, replaced);
        } if (const call *c = dynamic_cast<const call *> (p); c != nullptr) {
            bool replacement_was_made = false;
            data::stack<expression> new_list;

            for (Expression z : c->Args) {
                expression replaced = replace_inner (z, rr);
                if (replaced != expression {}) {
                    replacement_was_made = true;
                    new_list <<= replaced;
                } else new_list <<= z;
            }

            expression replaced = replace (c->Fun, rr);
            if (replaced == expression {}) {
                if (!replacement_was_made) return expression {};
                replaced = c->Fun;
            }

            return call::make (replaced, data::reverse (new_list));
        }

        return expression {};
    }

    expression replace (Expression e, replacements rr) {
        if (e == expression {}) return e;
        expression replaced = replace_inner (e, rr);
        if (replaced == expression {}) return e;
        return replaced;
    }

}
