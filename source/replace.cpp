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
        } else if (const binop *b = dynamic_cast<const binop *> (p); b != nullptr) {
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
            return binop::make (b->Operand, new_list);
        } if (const unop *u = dynamic_cast<const unop *> (p); u != nullptr) {
            expression replaced = replace_inner (u->Body, rr);
            return replaced == expression {} ? expression {} : unop::make (u->Operand, replaced);
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

    expression replace (Expression exp, replacements rr) {
        if (exp == expression {}) return exp;
        expression replaced = replace_inner (exp, rr);
        if (replaced == expression {}) return exp;
        return replaced;
    }

    using mr = match_result;

    mr match_inner (Machine m, Pattern patt, Expression evaluated) {

        const form *z = patt.get ();
        const form *n = evaluated.get ();

        if (z == n || z == nullptr) return mr {yes};

        const node *nn = dynamic_cast<const node *> (n);
        if (nn == nullptr) throw data::exception {"invalid expression found in match"};

        if (const blank *b = dynamic_cast<const blank *> (z); b != nullptr) {
            return b->Name != "" ? mr {replacements {{b->Name, evaluated}}} : mr {yes};
        }

        if (const typed *t = dynamic_cast<const typed *> (z); t != nullptr) {
            mr r = match (m, t->Match, evaluated);
            if (intuit (r) != yes) return r;
            if (t->Required.castable (m, evaluated) == yes) return r;
        }

        // note here we check the expression first .
        if (const symbol *x = dynamic_cast<const symbol *> (n); x != nullptr) {
            const symbol *y = dynamic_cast<const symbol *> (z);
            return y != nullptr && *x == *y ? yes : unknown;
        }

        if (const unop *u = dynamic_cast<const unop *> (z); u != nullptr) {
            const unop *v = dynamic_cast<const unop *> (n);
            if (v == nullptr || v->Operand != u->Operand) return {no};
            return match (m, u->Body, v->Body);
        }

        if (const binop *b = dynamic_cast<const binop *> (z); b != nullptr) {
            const binop *c = dynamic_cast<const binop *> (n);
            if (c == nullptr || b->Operand != c->Operand) return {no};
            return m.match (b->Body, c->Body);
        }

        if (const call *fx = dynamic_cast<const call *> (z); fx != nullptr) {
            const call *gx = dynamic_cast<const call *> (n);
            if (gx == nullptr) return {no};
            auto rf = match (m, fx->Fun, gx->Fun);
            if (intuit (rf) != yes) return rf;
            auto rx = m.match (data::stack<pattern> (fx->Args), gx->Args);
            if (intuit (rx) != yes) return rx;
            try {
                return *rf & *rx;
                // will be thrown if these maps have any of the same keys.
            } catch (replacements::key_already_exists) {
                return {no};
            }
        }

        if (const list *jk = dynamic_cast<const list *> (z); jk != nullptr) {
            const list *mn = dynamic_cast<const list *> (n);
            if (mn == nullptr || jk->List.size () != mn->List.size ()) return {no};

            replacements r {};
            auto jkl = jk->List;
            auto mno = mn->List;
            while (!data::empty (jkl)) {
                auto rr = match (m, pattern (data::first (jkl)), data::first (mno));
                if (intuit (rr) != yes) return rr;
                jkl = data::rest (jkl);
                mno = data::rest (mno);
                try {
                    r = r & *rr;
                    // will be thrown if these maps have any of the same keys.
                } catch (replacements::key_already_exists) {
                    return {no};
                }
            }
            return r;
        }

        if (const value *v = dynamic_cast<const value *> (z); v != nullptr) {
            const value *q = dynamic_cast<const value *> (n);
            if (q == nullptr) return {no};
            return *v == *q ? mr {yes} : mr {no};
        }

        return {no};
    }

    // we need a machine because we need to look up definitions.
    match_result match (Machine m, Pattern patt, Expression expr) {
        return match_inner (m, patt, m.evaluate (expr));
    }

}
