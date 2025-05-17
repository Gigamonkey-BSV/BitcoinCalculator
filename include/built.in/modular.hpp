#ifndef BITCOIN_CALCULATOR_BUILTIN_MODULAR
#define BITCOIN_CALCULATOR_BUILTIN_MODULAR

#include <built.in/scriptnum.hpp>
#include <gigamonkey/secp256k1.hpp>

namespace Diophant {

    namespace secp256k1 = Gigamonkey::secp256k1;

    bool coord_equal (const data::uint256 &x, const data::uint256 &y);
    bool coord_unequal (const data::uint256 &x, const data::uint256 &y);
    bool coord_greater_equal (const data::uint256 &x, const data::uint256 &y);
    bool coord_less_equal (const data::uint256 &x, const data::uint256 &y);
    bool coord_greater (const data::uint256 &x, const data::uint256 &y);
    bool coord_less (const data::uint256 &x, const data::uint256 &y);

    data::uint256 coord_negate (const data::uint256 &x);
    data::uint256 coord_plus (const data::uint256 &x, const data::uint256 &y);
    data::uint256 coord_minus (const data::uint256 &x, const data::uint256 &y);
    data::uint256 coord_times (const data::uint256 &x, const data::uint256 &y);

    bool secret_equal (const data::uint256 &x, const data::uint256 &y);
    bool secret_unequal (const data::uint256 &x, const data::uint256 &y);
    bool secret_greater_equal (const data::uint256 &x, const data::uint256 &y);
    bool secret_less_equal (const data::uint256 &x, const data::uint256 &y);
    bool secret_greater (const data::uint256 &x, const data::uint256 &y);
    bool secret_less (const data::uint256 &x, const data::uint256 &y);

    data::uint256 secret_negate (const data::uint256 &x);
    data::uint256 secret_plus (const data::uint256 &x, const data::uint256 &y);
    data::uint256 secret_minus (const data::uint256 &x, const data::uint256 &y);
    data::uint256 secret_times (const data::uint256 &x, const data::uint256 &y);

    data::uint256 secret_invert (const data::uint256 &x);
    data::uint256 secret_divide (const data::uint256 &x, const data::uint256 &y);

    data::uint256 secret_power (const data::uint256 &x, const data::Z &y);

    data::uint256 coord_invert (const data::uint256 &x);
    data::uint256 coord_divide (const data::uint256 &x, const data::uint256 &y);

    data::uint256 coord_power (const data::uint256 &x, const data::Z &y);

    bool secret_valid (const data::uint256 &x);
    bool coord_valid (const data::uint256 &x);

}

#endif
