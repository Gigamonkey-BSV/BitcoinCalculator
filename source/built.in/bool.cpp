
#include <built.in/bool.hpp>

namespace Diophant {

    bool bool_not (bool x) {
        return !x;
    }

    bool bool_and (bool x, bool y) {
        return x && y;
    }

    bool bool_or (bool x, bool y) {
        return x || y;
    }

    bool bool_implies (bool x, bool y) {
        return y || !x;
    }

    bool bool_xor (bool x, bool y) {
        return x != y;
    }

    bool bool_nand (bool x, bool y) {
        return ! (x && y);
    }

    bool bool_nor (bool x, bool y) {
        return ! (x || y);
    }

}

