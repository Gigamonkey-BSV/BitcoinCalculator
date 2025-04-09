#include <type.hpp>

namespace Diophant {

    // note: this is not the final version.
    impartial_ordering operator <=> (Type a, Type b) {
        return static_cast<Expression> (a) == static_cast<Expression> (b) ?
            impartial_ordering::equal : impartial_ordering::disjoint;
    }

    impartial_ordering operator && (impartial_ordering a, impartial_ordering b) {
        if (a == b) return a;

        if (a == impartial_ordering::disjoint || b == impartial_ordering::disjoint) return impartial_ordering::disjoint;

        if (a == impartial_ordering::equal) return b;
        if (b == impartial_ordering::equal) return b;

        return impartial_ordering::nonempty_complements;
    }

}
