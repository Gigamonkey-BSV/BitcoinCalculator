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
    Bitcoin::integer scriptnum_bool_not (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_bool_and (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bool_or (const Bitcoin::integer &x, const Bitcoin::integer &y);

    // bit operations
    Bitcoin::integer scriptnum_bit_not (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_bit_and (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bit_xor (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bit_or (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_identical (const Bitcoin::integer &x, const Bitcoin::integer &y);

    // comparisons
    Bitcoin::integer scriptnum_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_unequal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_greater_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_less_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_greater (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_less (const Bitcoin::integer &x, const Bitcoin::integer &y);

    // arithmetic
    Bitcoin::integer scriptnum_negate (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_plus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_minus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_times (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_divide (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_mod (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer scriptnum_abs (const Bitcoin::integer &x);

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const data::N &y);

}

#endif
