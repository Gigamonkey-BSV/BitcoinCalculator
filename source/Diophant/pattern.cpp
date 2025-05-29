#include <Diophant/pattern.hpp>
#include <Diophant/value.hpp>
#include <Diophant/type.hpp>
#include <Diophant/values/list.hpp>

namespace Diophant {
    impartial_ordering pattern_compare (Machine m, Expression A, Expression B);

    impartial_ordering pattern_compare (Machine m, const node *a, const node *b) {

        if (const value *v = dynamic_cast<const value *> (a); v != nullptr) {
            const value *w = dynamic_cast<const value *> (b);
            if (w == nullptr) return impartial_ordering::disjoint;
            return *v == *w ? impartial_ordering::equal : impartial_ordering::disjoint;
        }

        if (const symbol *x = dynamic_cast<const symbol *> (a); x != nullptr) {
            const symbol *y = dynamic_cast<const symbol *> (b);
            if (x == nullptr) return impartial_ordering::disjoint;
            return *x == *y ? impartial_ordering::equal : impartial_ordering::disjoint;
        }

        if (const unop *u = dynamic_cast<const unop *> (a); u != nullptr) {
            const unop *v = dynamic_cast<const unop *> (b);
            if (v == nullptr) return impartial_ordering::disjoint;
            if (u->Operand != v->Operand) return impartial_ordering::disjoint;
            return pattern_compare (m, u->Body, v->Body);
        }

        if (const binop *b = dynamic_cast<const binop *> (a); b != nullptr) {
            const binop *c = dynamic_cast<const binop *> (b);
            if (c == nullptr) return impartial_ordering::disjoint;
            if (b->Operand != c->Operand) return impartial_ordering::disjoint;
            data::stack<expression> j = b->Body;
            data::stack<expression> k = c->Body;
            if (j.size () != k.size ()) return impartial_ordering::disjoint;
            impartial_ordering compare = impartial_ordering::equal;
            while (!data::empty (j)) {
                compare = compare && pattern_compare (m, j.first (), k.first ());
                if (compare == impartial_ordering::disjoint) return impartial_ordering::disjoint;
                j = data::rest (j);
                k = data::rest (k);
            }
            return compare;
        }

        if (const list *ll = dynamic_cast<const list *> (a); ll != nullptr) {
            const list *mm = dynamic_cast<const list *> (b);
            if (mm == nullptr) return impartial_ordering::disjoint;
            data::stack<expression> j = ll->List;
            data::stack<expression> k = mm->List;
            if (j.size () != k.size ()) return impartial_ordering::disjoint;
            impartial_ordering compare = impartial_ordering::equal;
            while (!data::empty (j)) {
                compare = compare && pattern_compare (m, j.first (), k.first ());
                if (compare == impartial_ordering::disjoint) return impartial_ordering::disjoint;
                j = data::rest (j);
                k = data::rest (k);
            }
            return compare;
        }

        if (const call *fx = dynamic_cast<const call *> (a); fx != nullptr) {
            const call *gx = dynamic_cast<const call *> (b);

            if (gx == nullptr) return impartial_ordering::disjoint;
            if (data::size (fx->Args) != data::size (gx->Args)) return impartial_ordering::disjoint;

            data::stack<expression> j = fx->Args;
            data::stack<expression> k = gx->Args;

            impartial_ordering compare = pattern_compare (m, fx->Fun, gx->Fun);

            while (!data::empty (j)) {
                if (compare == impartial_ordering::disjoint) return impartial_ordering::disjoint;
                compare = compare && pattern_compare (m, j.first (), k.first ());
                j = data::rest (j);
                k = data::rest (k);
            }

            return compare;

        }

        throw data::exception {} << "incomplete method: pattern " << a << " <=> " << b;
    }

    impartial_ordering pattern_compare (Machine m, const form *a, const node *b) {
        if (const node *n = dynamic_cast<const node *> (a); n != nullptr)
            return pattern_compare (m, n, b);

        if (const blank *n = dynamic_cast<const blank *> (a); n != nullptr) return impartial_ordering::superset;

        if (const typed *n = dynamic_cast<const typed *> (a); n != nullptr) {
            impartial_ordering cmp = pattern_compare (m, n->Match.get (), b);
            if (cmp == impartial_ordering::disjoint) return impartial_ordering::disjoint;

            // TODO this is incorrect but it is the best we can do for now.
            return impartial_ordering::disjoint;
        }

        throw data::exception {} << "incomplete method: pattern " << a << " <=> " << b;
    }

    impartial_ordering pattern_compare (Machine m, Expression A, Expression B) {

        const form *a = A.get ();
        const form *b = B.get ();

        if (a == nullptr || b == nullptr) throw data::exception {} << "cannot compare null patterns";

        if (const node *n = dynamic_cast<const node *> (a); n != nullptr)
            return -pattern_compare (m, b, n);

        if (const node *n = dynamic_cast<const node *> (b); n != nullptr)
            return pattern_compare (m, a, n);

        if (const blank *n = dynamic_cast<const blank *> (a); n != nullptr) {
            if (const blank *m = dynamic_cast<const blank *> (b); m != nullptr)
                return impartial_ordering::equal;
            else return impartial_ordering::superset;
        }

        if (const blank *u = dynamic_cast<const blank *> (b); u != nullptr)
            return impartial_ordering::subset;

        {
            const typed *u = dynamic_cast<const typed *> (a);
            const typed *v = dynamic_cast<const typed *> (b);
            if (u != nullptr && v != nullptr)
                return compare (m, u->Required, v->Required) && pattern_compare (m, u->Match, v->Match);
        }

        throw data::exception {} << "incomplete method: pattern " << A << " <=> " << B;
    }

    impartial_ordering compare (Machine m, Pattern A, Pattern B) {
        return pattern_compare (m, A, B);
    }


}

