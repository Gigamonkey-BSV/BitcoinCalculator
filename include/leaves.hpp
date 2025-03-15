#ifndef BITCOIN_CALCULATOR_LEAVES
#define BITCOIN_CALCULATOR_LEAVES

#include <expression.hpp>
#include <data/function.hpp>
#include <gigamonkey/wif.hpp>
#include <gigamonkey/address.hpp>
#include <gigamonkey/numbers.hpp>

namespace Diophant {

    template <typename T> struct leaf : node {
        T Value;
    };

    using Dstring = leaf<string>;
    using Dinteger = leaf<Bitcoin::integer>;
    using Dpubkey = leaf<Gigamonkey::secp256k1::pubkey>;
    using Dsecret = leaf<Gigamonkey::secp256k1::secret>;
    template <typename Y, typename ... X> using built_in_function = leaf<std::function<Y (X...)>>;

}

#endif


