#include <Diophant/replace.hpp>
#include <Diophant/values/list.hpp>
#include <Diophant/values/struct.hpp>
#include <Diophant/values/lambda.hpp>

namespace Diophant {

    // return null if no replacement is made.
    expression replace_inner (Expression e, replacements rr) {
        const form *p = e.get ();
        if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr) {
            const expression *r = rr.contains (*x);
            return r != nullptr ? *r : expression {};
        }

        if (const lambda *q = dynamic_cast<const lambda *> (p); q != nullptr) {
            // if the variables in the lambda expression contain
            // any of the replacement symbols, they are removed
            // from the replacements.
            data::stack<symbol> removed;
            for (const symbol &x : q->Args) 
                if (rr.contains (x)) 
                    removed >>= x;

            for (const symbol &x : removed) rr = data::remove (rr, x);

            if (expression replaced = replace_inner (q->Body, rr); replaced != nullptr)
                return lambda::make (q->Args, replaced);
            else return expression {};
        }

        if (const list *ls = dynamic_cast<const list *> (p); ls != nullptr) {
            bool replacement_was_made = false;
            data::stack<expression> new_list;

            for (const expression z : ls->List) {
                expression replaced = replace_inner (z, rr);
                if (replaced != expression {}) {
                    new_list >>= replaced;
                } else new_list >>= z;
            }

            return replacement_was_made ? list::make (reverse (new_list)): expression {};
        }

        if (const dstruct *dt = dynamic_cast<const dstruct *> (p); dt != nullptr) {
            throw data::exception {} << "replace struct: we don't handle this case yet.";
        }

        if (const binop *b = dynamic_cast<const binop *> (p); b != nullptr) {
            bool replacement_was_made = false;
            data::stack<expression> new_list;

            for (Expression z : b->Body) {
                expression replaced = replace_inner (z, rr);
                if (replaced != expression {}) {
                    replacement_was_made = true;
                    new_list >>= replaced;
                } else new_list >>= z;
            }

            if (!replacement_was_made) return expression {};
            return binop::make (b->Operand, new_list);
        }

        if (const unop *u = dynamic_cast<const unop *> (p); u != nullptr) {
            expression replaced = replace_inner (u->Body, rr);
            return replaced == expression {} ? expression {} : unop::make (u->Operand, replaced);
        }

        if (const call *c = dynamic_cast<const call *> (p); c != nullptr) {
            bool replacement_was_made = false;

            expression replaced = replace (c->Fun, rr);
            if (replaced != expression {}) replacement_was_made = true;
            else replaced = c->Fun;

            data::stack<expression> new_list;
            for (Expression z : c->Args) {
                expression replaced = replace_inner (z, rr);
                if (replaced != expression {}) {
                    replacement_was_made = true;
                    new_list >>= replaced;
                } else new_list >>= z;
            }

            return replacement_was_made ?
                call::make (replaced, data::reverse (new_list)):
                expression {};
        }

        if (const let *l = dynamic_cast<const let *> (p); l != nullptr) {
            bool replacement_was_made = false;
            data::dispatch<const symbol, expression> new_symbols;

            replacements r = rr;

            for (const auto &[k, v] : l->Values) {
                r = r.remove (k);

                expression replaced = replace_inner (v, r);
                if (replaced != expression {}) {
                    replacement_was_made = true;
                    new_symbols >>= data::entry<const symbol, expression> {k, replaced};
                } else new_symbols >>= data::entry<const symbol, expression> {k, v};
            }

            expression replaced = replace_inner (l->In, r);
            if (replaced != expression {}) replacement_was_made = true;
            else replaced = l->In;

            return replacement_was_made ?
                let::make (reverse (new_symbols), replaced):
                expression {};
        }

        if (const dif *df = dynamic_cast<const dif *> (p); df != nullptr) {

            bool replacement_was_made = false;

            expression if_new = replace_inner (df->If, rr);
            expression then_new = replace_inner (df->Then, rr);
            expression else_new = replace_inner (df->Else, rr);

            if (if_new != expression {}) {
                replacement_was_made = true;
            } else if_new = df->If;

            if (then_new != expression {}) {
                replacement_was_made = true;
            } else then_new = df->Then;

            if (else_new != expression {}) {
                replacement_was_made = true;
            } else else_new = df->Else;

            return replacement_was_made ? dif::make (if_new, then_new, else_new): expression {};
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
            intuit is_castable = t->Required.castable (m, evaluated);
            return is_castable == yes ? r : mr {is_castable};
        }

        // note here we check the expression first .
        if (const symbol *x = dynamic_cast<const symbol *> (n); x != nullptr) {
            const symbol *y = dynamic_cast<const symbol *> (z);
            // note: previously we had yes : unknown here because it would be
            // possible for an unevaluated symbol to be equal to a different one.
            // However, this turned out to be unfeasable. We have to make sure that
            // the expression is fully evaluated before we check casts.
            return y != nullptr && *x == *y ? yes : no;
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
                return *rf | *rx;
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
            while (!empty (jkl)) {
                auto rr = match (m, pattern (first (jkl)), first (mno));
                if (intuit (rr) != yes) return rr;
                jkl = rest (jkl);
                mno = rest (mno);
                try {
                    r = r | *rr;
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
