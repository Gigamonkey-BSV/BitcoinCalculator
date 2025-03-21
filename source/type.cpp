#include <type.hpp>

namespace Diophant {

    // note: this is not the final version.
    impartial_ordering operator <=> (Type a, Type b) {
        return static_cast<Expression> (a) == static_cast<Expression> (b) ?
            impartial_ordering::equal : impartial_ordering::disjoint;
    }

}
