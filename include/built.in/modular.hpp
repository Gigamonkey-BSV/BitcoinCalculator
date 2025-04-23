#ifndef BITCOIN_CALCULATOR_BUILTIN_MODULAR
#define BITCOIN_CALCULATOR_BUILTIN_MODULAR

#include <built.in/scriptnum.hpp>
#include <gigamonkey/secp256k1.hpp>

namespace Diophant {

    namespace secp256k1 = Gigamonkey::secp256k1;
    using uint256 = data::uint256_little;
    using uint512 = data::uint512_little;

    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const uint256 &y);
    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const uint256 &y);

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const uint256 &y);
    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const uint256 &y);

    std::tuple<Bitcoin::integer, Bitcoin::integer> scriptnum_split (const Bitcoin::integer &x, const uint256 &y);

    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const uint256 &y);

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const uint256 &y);

    bool coord_equal (const uint256 &x, const uint256 &y);
    bool coord_unequal (const uint256 &x, const uint256 &y);
    bool coord_greater_equal (const uint256 &x, const uint256 &y);
    bool coord_less_equal (const uint256 &x, const uint256 &y);
    bool coord_greater (const uint256 &x, const uint256 &y);
    bool coord_less (const uint256 &x, const uint256 &y);

    uint256 coord_negate (const uint256 &x);
    uint256 coord_plus (const uint256 &x, const uint256 &y);
    uint256 coord_minus (const uint256 &x, const uint256 &y);
    uint256 coord_times (const uint256 &x, const uint256 &y);

    bool secret_equal (const uint256 &x, const uint256 &y);
    bool secret_unequal (const uint256 &x, const uint256 &y);
    bool secret_greater_equal (const uint256 &x, const uint256 &y);
    bool secret_less_equal (const uint256 &x, const uint256 &y);
    bool secret_greater (const uint256 &x, const uint256 &y);
    bool secret_less (const uint256 &x, const uint256 &y);

    uint256 secret_negate (const uint256 &x);
    uint256 secret_plus (const uint256 &x, const uint256 &y);
    uint256 secret_minus (const uint256 &x, const uint256 &y);
    uint256 secret_times (const uint256 &x, const uint256 &y);

    uint256 secret_invert (const uint256 &x);
    uint256 secret_divide (const uint256 &x, const uint256 &y);

    uint256 secret_power (const uint256 &x, const uint256 &y);

    uint256 coord_invert (const uint256 &x);
    uint256 coord_divide (const uint256 &x, const uint256 &y);

    uint256 coord_power (const uint256 &x, const uint256 &y);

    bool secret_valid (const uint256 &x);
    bool coord_valid (const uint256 &x);

}

#endif
