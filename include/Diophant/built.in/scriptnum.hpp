#ifndef BITCOIN_CALCULATOR_BUILTIN_SCRIPTNUM
#define BITCOIN_CALCULATOR_BUILTIN_SCRIPTNUM

#include <gigamonkey/numbers.hpp>

namespace Diophant {

    namespace Bitcoin = Gigamonkey::Bitcoin;

    // return the size of a scriptnum as a scriptnum
    data::bytes scriptnum_size (const data::bytes &x);

    bool scriptnum_minimal (const data::bytes &x);

    // return the minimal size of a scriptnum as a scriptnum.
    data::bytes scriptnum_minimal_size (const data::bytes &x);

    // trim the scriptnum to minimal size.
    data::bytes scriptnum_minimize (const data::bytes &x);
    data::bytes scriptnum_resize (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_resize (const data::bytes &x, const data::N &y);

    // bool operations
    data::bytes scriptnum_bool_not (const data::bytes &x);
    data::bytes scriptnum_bool_and (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_bool_or (const data::bytes &x, const data::bytes &y);

    // bit operations
    data::bytes scriptnum_bit_not (const data::bytes &x);
    data::bytes scriptnum_bit_and (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_bit_xor (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_bit_or (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_identical (const data::bytes &x, const data::bytes &y);

    // comparisons
    data::bytes scriptnum_equal (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_unequal (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_greater_equal (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_less_equal (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_greater (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_less (const data::bytes &x, const data::bytes &y);

    bool scriptnum_is_negative (const data::bytes &x);

    bool scriptnum_cast_to_bool (const data::bytes &x);

    data::N cast_scriptnum_to_N (const data::bytes &);
    data::Z cast_scriptnum_to_Z (const data::bytes &);
    data::bytes cast_N_to_scriptnum (const data::N &);
    data::bytes cast_Z_to_scriptnum (const data::Z &);

    // arithmetic
    data::bytes scriptnum_negate (const data::bytes &x);
    data::bytes scriptnum_plus (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_minus (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_times (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_divide (const data::bytes &x, const data::bytes &y);
    data::bytes scriptnum_mod (const data::bytes &x, const data::bytes &y);

    data::bytes scriptnum_abs (const data::bytes &x);

    data::bytes scriptnum_power (const data::bytes &x, const data::N &y);

    data::bytes set_sign_bit (const data::bytes &);

}

#endif
