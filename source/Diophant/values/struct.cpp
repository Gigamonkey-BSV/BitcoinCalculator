#include <Diophant/values/struct.hpp>
#include <Diophant/nodes.hpp>

namespace Diophant {
    std::ostream &dstruct::write (std::ostream &o) const {
        o << "{";
        auto b = Values.begin ();
        if (b != Values.end ()) {
            o << b->Key << " -> " << b->Value;
            while (true) {
                b++;
                if (b == Values.end ()) break;
                o << ", " << b->Key << " -> " << b->Value;
            }
        }
        return o << "}";
    }

    bool dstruct::cast (const machine &m, const node &n) const {
        const dstruct *xx = dynamic_cast<const dstruct *> (&n);
        if (xx == nullptr) return false;

        if (xx->Values.size () != Values.size ()) return false;
        auto la = this->Values.begin ();
        auto lb = xx->Values.begin ();
        while (la != this->Values.end ()) {
            if (la->Key != lb->Key) return false;

            const expression &a = la->Value;
            const expression &b = la->Value;

            const value *v = dynamic_cast<const value *> (a.get ());
            if (v == nullptr) return false;

            const node *x = dynamic_cast<const node *> (b.get ());
            if (x == nullptr) return false;

            if (!v->cast (m, *x)) return false;

            la++;
            lb++;
        }

        return true;
    }
}
