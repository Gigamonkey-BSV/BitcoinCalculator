#include <Diophant/pattern.hpp>
#include <Diophant/value.hpp>
#include <Diophant/type.hpp>
#include <Diophant/values/list.hpp>

namespace Diophant {

    bool disjoint (Machine m, Pattern A, Pattern B) {
        const form *a = A.get ();
        const form *b = B.get ();

        if (a == nullptr || b == nullptr) return !(a == nullptr && b == nullptr);

        {
            const blank *n = dynamic_cast<const blank *> (a);
            const blank *m = dynamic_cast<const blank *> (b);

            if (n != nullptr || m != nullptr) return false;
        }

        if (const default_value *u = dynamic_cast<const default_value *> (a); u != nullptr)
            return disjoint (m, B, u->Match);

        if (const typed *u = dynamic_cast<const typed *> (a); u != nullptr) {
            if (const typed *v = dynamic_cast<const typed *> (b); v != nullptr) {
                if (disjoint (m, u->Match, v->Match)) return true;
                return compare (m, u->Required, v->Required) == impartial_ordering::disjoint;
            }

            if (disjoint (m, B, u->Match)) return true;
            return yes != u->Required.castable (m, B);
        }

        if (const symbol *x = dynamic_cast<const symbol *> (a); x != nullptr) {
            const symbol *y = dynamic_cast<const symbol *> (b);
            if (y == nullptr) return true;
            return *x != *y;
        }

        if (const unop *u = dynamic_cast<const unop *> (a); u != nullptr) {
            const unop *v = dynamic_cast<const unop *> (b);
            if (v == nullptr) return true;
            if (u->Operand != v->Operand) return true;
            return disjoint (m, u->Body, v->Body);
        }

        if (const binop *bi = dynamic_cast<const binop *> (a); bi != nullptr) {
            const binop *ci = dynamic_cast<const binop *> (b);
            if (ci == nullptr) return true;
            if (bi->Operand != ci->Operand) return true;
            data::stack<expression> j = bi->Body;
            data::stack<expression> k = ci->Body;
            if (j.size () != k.size ()) return true;
            while (!empty (j)) {
                if (disjoint (m, first (j), first (k))) return true;
                j = rest (j);
                k = rest (k);
            }
            return false;
        }

        if (const list *ll = dynamic_cast<const list *> (a); ll != nullptr) {
            const list *mm = dynamic_cast<const list *> (b);
            if (mm == nullptr) return true;
            data::stack<expression> j = ll->List;
            data::stack<expression> k = mm->List;
            if (j.size () != k.size ()) return true;
            while (!empty (j)) {
                if (disjoint (m, first (j), first (k))) return true;
                j = rest (j);
                k = rest (k);
            }
            return false;
        }

        if (const call *fx = dynamic_cast<const call *> (a); fx != nullptr) {
            const call *gx = dynamic_cast<const call *> (b);
            if (gx == nullptr) return true;
            if (data::size (fx->Args) != data::size (gx->Args)) return true;

            data::stack<expression> j = fx->Args;
            data::stack<expression> k = gx->Args;

            if (disjoint (m, fx->Fun, gx->Fun)) return true;

            while (!empty (j)) {
                if (disjoint (m, first (j), first (k))) return true;
                j = rest (j);
                k = rest (k);
            }

            return false;

        }

        if (const value *v = dynamic_cast<const value *> (a); v != nullptr) {
            const value *w = dynamic_cast<const value *> (b);
            if (w == nullptr) return true;
            return *v != *w;
        }

        return false;
    }

    impartial_ordering compare (Machine m, Pattern A, Pattern B) {
        if (disjoint (m, A, B)) return impartial_ordering::disjoint;

        bool match_left_to_right {match (m, A, B)};
        bool match_right_to_left {match (m, B, A)};

        if (match_left_to_right && match_right_to_left) return impartial_ordering::equal;

        if (match_left_to_right) return impartial_ordering::superset;
        if (match_right_to_left) return impartial_ordering::subset;

        return impartial_ordering::nonempty_complements;
    }

    expression operator | (Expression a, Expression b) {
        return binop::make (binary_operand::intuitionistic_or, {a, b});
    }

}

