#ifndef BITCOIN_CALCULATOR_BUILTIN_SCRIPTNUM
#define BITCOIN_CALCULATOR_BUILTIN_SCRIPTNUM

#include <gigamonkey/numbers.hpp>

namespace Diophant {

    namespace Bitcoin = Gigamonkey::Bitcoin;

    Bitcoin::integer scriptnum_cat (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const Bitcoin::integer &y);

    std::tuple<Bitcoin::integer, Bitcoin::integer> scriptnum_split (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer bitcoin_checksum (const Bitcoin::integer &x);

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

    Bitcoin::integer scriptnum_size (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_minimal_size (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_minimal (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_is_minimal (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const Bitcoin::integer &y);

    // arithmetic
    Bitcoin::integer scriptnum_negate (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_plus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_minus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_times (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_divide (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_mod (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer scriptnum_abs (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const Bitcoin::integer &y);

}

#endif
