#include <pattern.hpp>
#include <value.hpp>
#include <values/list.hpp>

namespace Diophant {
    impartial_ordering pattern_compare (Expression A, Expression B);

    impartial_ordering pattern_compare (const node *a, const node *b) {
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

        if (const unary_operation *u = dynamic_cast<const unary_operation *> (a); u != nullptr) {
            const unary_operation *v = dynamic_cast<const unary_operation *> (b);
            if (v == nullptr) return impartial_ordering::disjoint;
            if (u->Operator != v->Operator) return impartial_ordering::disjoint;
            return pattern_compare (u->Body, v->Body);
        }

        if (const binary_operation *b = dynamic_cast<const binary_operation *> (a); b != nullptr) {
            const binary_operation *c = dynamic_cast<const binary_operation *> (b);
            if (c == nullptr) return impartial_ordering::disjoint;
            if (b->Operator != c->Operator) return impartial_ordering::disjoint;
            data::stack<expression> l = b->Body;
            data::stack<expression> m = c->Body;
            if (l.size () != m.size ()) return impartial_ordering::disjoint;
            impartial_ordering compare = impartial_ordering::equal;
            while (!data::empty (l)) {
                compare = compare && pattern_compare (l.first (), m.first ());
                if (compare == impartial_ordering::disjoint) return impartial_ordering::disjoint;
                l = data::rest (l);
                m = data::rest (m);
            }
            return compare;
        }

        if (const list *ll = dynamic_cast<const list *> (a); ll != nullptr) {
            const list *mm = dynamic_cast<const list *> (b);
            if (mm == nullptr) return impartial_ordering::disjoint;
            data::stack<expression> l = ll->List;
            data::stack<expression> m = mm->List;
            if (l.size () != m.size ()) return impartial_ordering::disjoint;
            impartial_ordering compare = impartial_ordering::equal;
            while (!data::empty (l)) {
                compare = compare && pattern_compare (l.first (), m.first ());
                if (compare == impartial_ordering::disjoint) return impartial_ordering::disjoint;
                l = data::rest (l);
                m = data::rest (m);
            }
            return compare;
        }

        throw data::exception {} << "incomplete method: pattern <=> ";
    }

    impartial_ordering pattern_compare (const form *a, const node *b) {
        if (const node *n = dynamic_cast<const node *> (a); n != nullptr)
            return pattern_compare (n, b);

        if (const blank *n = dynamic_cast<const blank *> (a); n != nullptr) return impartial_ordering::superset;

        if (const typed *n = dynamic_cast<const typed *> (a); n != nullptr) {
            impartial_ordering cmp = pattern_compare (n->Match.get (), b);
            if (cmp == impartial_ordering::disjoint) return impartial_ordering::disjoint;

            // TODO this is incorrect but it is the best we can do for now.
            return impartial_ordering::disjoint;
        }

        throw data::exception {} << "incomplete method: pattern <=> ";
    }

    impartial_ordering pattern_compare (Expression A, Expression B) {

        const form *a = A.get ();
        const form *b = B.get ();

        if (a == nullptr || b == nullptr) throw data::exception {} << "cannot compare null patterns";

        if (const node *n = dynamic_cast<const node *> (a); n != nullptr)
            return -pattern_compare (b, n);

        if (const node *n = dynamic_cast<const node *> (b); n != nullptr)
            return pattern_compare (a, n);

        if (const blank *n = dynamic_cast<const blank *> (a); n != nullptr) {
            if (const blank *m = dynamic_cast<const blank *> (b); m != nullptr)
                return impartial_ordering::equal;
            else return impartial_ordering::superset;
        }

        if (const blank *m = dynamic_cast<const blank *> (b); m != nullptr)
            return impartial_ordering::subset;

        {
            const typed *n = dynamic_cast<const typed *> (a);
            const typed *m = dynamic_cast<const typed *> (b);
            if (n != nullptr && m != nullptr)
                return n->Required <=> m->Required && pattern_compare (n->Match, m->Match);
        }

        throw data::exception {} << "incomplete method: pattern " << A << " <=> " << B;
    }

    impartial_ordering operator <=> (Pattern A, Pattern B) {
        return pattern_compare (A, B);
    }


}

