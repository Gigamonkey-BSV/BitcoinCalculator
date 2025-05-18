#ifndef BITCOIN_CALCULATOR_BUILTIN_BOOL
#define BITCOIN_CALCULATOR_BUILTIN_BOOL

namespace Diophant {

    bool bool_not (bool x);
    bool bool_and (bool x, bool y);
    bool bool_or (bool x, bool y);
    bool bool_implies (bool x, bool y);
    bool bool_xor (bool x, bool y);
    bool bool_nand (bool x, bool y);
    bool bool_nor (bool x, bool y);

}

#endif


