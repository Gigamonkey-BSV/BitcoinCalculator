#ifndef BITCOIN_CALCULATOR_BUILTIN_MODULAR
#define BITCOIN_CALCULATOR_BUILTIN_MODULAR

#include <Diophant/built.in/scriptnum.hpp>
#include <gigamonkey/secp256k1.hpp>

namespace Diophant {

    namespace secp256k1 = Gigamonkey::secp256k1;

    bool coord_equal (const data::N &x, const data::N &y);
    bool coord_unequal (const data::N &x, const data::N &y);
    bool coord_greater_equal (const data::N &x, const data::N &y);
    bool coord_less_equal (const data::N &x, const data::N &y);
    bool coord_greater (const data::N &x, const data::N &y);
    bool coord_less (const data::N &x, const data::N &y);

    data::N coord_negate (const data::N &x);
    data::N coord_plus (const data::N &x, const data::N &y);
    data::N coord_minus (const data::N &x, const data::N &y);
    data::N coord_times (const data::N &x, const data::N &y);

    bool secret_equal (const data::N &x, const data::N &y);
    bool secret_unequal (const data::N &x, const data::N &y);
    bool secret_greater_equal (const data::N &x, const data::N &y);
    bool secret_less_equal (const data::N &x, const data::N &y);
    bool secret_greater (const data::N &x, const data::N &y);
    bool secret_less (const data::N &x, const data::N &y);

    data::N secret_negate (const data::N &x);
    data::N secret_plus (const data::N &x, const data::N &y);
    data::N secret_minus (const data::N &x, const data::N &y);
    data::N secret_times (const data::N &x, const data::N &y);

    data::N secret_invert (const data::N &x);
    data::N secret_divide (const data::N &x, const data::N &y);

    data::N secret_power (const data::N &x, const data::Z &y);

    data::N coord_invert (const data::N &x);
    data::N coord_divide (const data::N &x, const data::N &y);

    data::N coord_power (const data::N &x, const data::Z &y);

    bool secret_valid (const data::N &x);
    bool coord_valid (const data::N &x);

}

#endif
