#include <Diophant/type.hpp>
#include <Diophant/machine.hpp>
#include <Diophant/value.hpp>

namespace Diophant {

    std::ostream &operator << (std::ostream &o, impartial_ordering i) {
        if (i == impartial_ordering {0}) return o << "\0";
        bool written = false;
        if (data::byte (i & impartial_ordering::equal)) {
            o << "equal";
            written = true;
        }
        if (data::byte (i & impartial_ordering::disjoint)) {
            if (written) o << " | ";
            o << "disjoint";
            written = true;
        }
        if (data::byte (i & impartial_ordering::subset)) {
            if (written) o << " | ";
            o << "subset";
            written = true;
        }
        if (data::byte (i & impartial_ordering::superset)) {
            if (written) o << " | ";
            o << "superset";
            written = true;
        }
        if (data::byte (i & impartial_ordering::nonempty_complements)) {
            if (written) o << " | ";
            o << "nonempty_complements";
            written = true;
        }
        return o;
    }

    impartial_ordering compare (Machine m, Type a, Type b) {
        const form *x = a.get ();

        if (x == nullptr) return b.get () == nullptr ? impartial_ordering::equal : impartial_ordering::superset;

        const node *n = dynamic_cast<const node *> (x);
        if (n == nullptr) {
            if (bool (match (m, pattern (a), b)))
                return impartial_ordering::superset | impartial_ordering::equal;
            else return impartial_ordering::disjoint | impartial_ordering::nonempty_complements | impartial_ordering::subset;
        }

        return type::compare (m, *n, b);
    }

    // note: this is not the final version.
    impartial_ordering type::compare (Machine m, const node &a, Type b) {
        const form *y = b.get ();

        if (y == nullptr) return impartial_ordering::subset;

        const node *n = dynamic_cast<const node *> (y);
        if (n == nullptr) throw data::exception {} << "I don't know how to handle this case now.";
        return a == *n ? impartial_ordering::equal : impartial_ordering::disjoint;
    }

    impartial_ordering operator && (impartial_ordering a, impartial_ordering b) {
        if (a == b) return a;

        if (a == impartial_ordering::disjoint || b == impartial_ordering::disjoint) return impartial_ordering::disjoint;

        if (a == impartial_ordering::equal) return b;
        if (b == impartial_ordering::equal) return a;

        return impartial_ordering::nonempty_complements;
    }

    namespace {

        intuit cast_symbol (const machine &m, const node &t, const symbol &x);
        intuit cast_call (const machine &, const node &t, const call &c);
        intuit cast_binop (const machine &, const node &t, const binop &E);
        intuit cast_unop (const machine &m, const node &t, const unop &E);
        intuit cast_let (const machine &m, const node &t, const let &E);
        intuit cast_if (const machine &m, const node &t, const let &E);

    }

    intuit type::castable (const machine &m, Expression E) const {
        data::log::indent abc {};
        DATA_LOG(debug) << "try to cast to " << E;
        const form *t = this->get ();
        const form *e = E.get ();

        if (this->get () == nullptr) return yes;
        if (e == nullptr) return unknown;

        const node *en = dynamic_cast<const node *> (e);
        // if e is actually a pattern, then the problem comes
        // down to whether
        if (en == nullptr) {
            // we do not have a universal type (since not all terms are typable)
            // therefore the blank is always more general than any type.
            if (const blank *b = dynamic_cast<const blank *> (e); b != nullptr)
                return no;

            if (const typed *t = dynamic_cast<const typed *> (e); t != nullptr) {
                impartial_ordering comparison = Diophant::compare (m, *this, t->Required);
                // TODO here we assume that t->Match is blank. This is not necessarily true
                // but it is not an important application to have it not blank.
                if (comparison == impartial_ordering::equal || comparison == impartial_ordering::superset) return yes;
                return no;
            }

            if (const default_value *dv = dynamic_cast<const default_value *> (e); dv != nullptr)
                return castable (m, dv->Match);

            throw data::exception {} << "Invalid cast.";
        }

        const node *tn = dynamic_cast<const node *> (t);
        // in this case we should try match rather than cast.
        if (tn == nullptr) return match (m, pattern (*this), E) ? yes : no;

        // check for alternatives
        if (const binop *bt = dynamic_cast<const binop *> (tn); bt != nullptr) {
            if (bt->Operand == binary_operand::intuitionistic_or) {
                for (const auto &x : bt->Body) {
                    intuit casted = type {x}.castable (m, E);
                    if (casted == no) continue;
                    return casted;
                }
            } else if (bt->Operand == binary_operand::intuitionistic_implies) {
                throw data::method::unimplemented {"cast to => "};
            } else if (bt->Operand == binary_operand::intuitionistic_and) {
                throw data::method::unimplemented {"cast to & "};
            }
        }

        if (const value *v = dynamic_cast<const value *> (e); v != nullptr)
            return v->cast (m, *tn) ? yes : no;

        if (const symbol *x = dynamic_cast<const symbol *> (e); x != nullptr)
            return cast_symbol (m, *tn, *x);

        if (const binop *b = dynamic_cast<const binop *> (e); b != nullptr)
            return cast_binop (m, *tn, *b);

        if (const unop *u = dynamic_cast<const unop *> (e); u != nullptr)
            return cast_unop (m, *tn, *u);

        if (const call *c = dynamic_cast<const call *> (e); c != nullptr)
            return cast_call (m, *tn, *c);

        throw data::exception {} << " we don't know how to cast this type";

        // TODO: try to evaluate the type.
    }

    namespace {

        intuit cast_symbol (const machine &m, const node &t, const symbol &x) {
            const symbol *cx = dynamic_cast<const symbol *> (&t);
            return cx != nullptr && *cx == x ? yes : no;
        }

        intuit cast_call (const machine &m, const node &t, const call &c) {
            const call *ct = dynamic_cast<const call *> (&t);
            if (ct == nullptr) return no;

            if (ct->Fun != c.Fun) return no;

            auto targ = ct->Args;
            auto carg = c.Args;
            if (size (targ) != size (carg)) return no;

            while (size (targ) > 0) {
                if (!type {first (targ)}.castable (m, first (carg))) return no;
                targ = rest (targ);
                carg = rest (carg);
            }

            return yes;
        }

        intuit cast_binop (const machine &m, const node &t, const binop &E) {
            const binop *bn = dynamic_cast<const binop *> (&t);
            if (bn == nullptr) return no;

            if (bn->Operand != E.Operand) return no;

            auto ba = bn->Body;
            auto bb = E.Body;
            if (size (ba) != size (bb)) return no;

            while (size (ba) > 0) {
                if (!type {first (ba)}.castable (m, first (bb))) return no;

                ba = rest (ba);
                bb = rest (bb);
            }

            return yes;
        }

        intuit cast_unop (const machine &m, const node &t, const unop &E) {
            const unop *un = dynamic_cast<const unop *> (&t);
            if (un == nullptr) return no;

            if (un->Operand != E.Operand) return no;

            if (!type {un->Body}.castable (m, E.Body)) return no;

            return yes;
        }
    }

}
