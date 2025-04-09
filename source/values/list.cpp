#include <values/list.hpp>

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

}
