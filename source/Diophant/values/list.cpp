#include <Diophant/values/list.hpp>
#include <Diophant/nodes.hpp>

namespace Diophant {

    std::ostream &list::write (std::ostream &o) const {
        o << "[";
        if (!data::empty (List)) {
            o << List.first ();
            auto r = List.rest ();
            while (!data::empty (r)) {
                o << ", " << r.first ();
                r = r.rest ();
            }
        }
        o << "]";
        return o;
    }

    bool inline list::cast (const machine &m, const node &n) const {
        if (const call *fx = dynamic_cast<const call *> (&n); fx != nullptr) {
            const symbol *tt = dynamic_cast<const symbol *> (fx->Fun.get ());
            if (tt == nullptr) return false;

            if (*tt != symbol {"list"}) return false;

            if (fx->Args.size () != 1) return false;

            const node *x = dynamic_cast<const node *> (fx->Args.first ().get ());
            if (x == nullptr) return false;

            for (const expression &ex : List) {

                const value *v = dynamic_cast<const value *> (ex.get ());
                if (v == nullptr) return false;

                if (!v->cast (m, *x)) return false;

            }

            return true;

        } else if (const list *ll = dynamic_cast<const list *> (&n); ll != nullptr) {
            if (ll->List.size () != List.size ()) return false;
            data::stack<expression> la;
            data::stack<expression> lb;
            while (!data::empty (la)) {
                const expression &a = la.first ();
                const expression &b = la.first ();

                const value *v = dynamic_cast<const value *> (a.get ());
                if (v == nullptr) return false;

                const node *x = dynamic_cast<const node *> (b.get ());
                if (x == nullptr) return false;

                if (!v->cast (m, *x)) return false;

                la = data::rest (la);
                lb = data::rest (lb);
            }

            return true;

        }

        return false;
    }
}
