#ifndef BITCOIN_CALCULATOR_LEAVES
#define BITCOIN_CALCULATOR_LEAVES

#include <expression.hpp>
#include <data/function.hpp>
#include <gigamonkey/wif.hpp>
#include <gigamonkey/address.hpp>
#include <gigamonkey/numbers.hpp>

namespace Diophant {

    namespace secp256k1 = Gigamonkey::secp256k1;
    using uint256 = data::uint256;
    using byte = data::byte;

    template <typename T> struct leaf : node {
        T Value;
        static expression make (const T &);
    };

    using Dbyte = leaf<byte>;
    using Dstring = leaf<string>;
    using Dscriptnum = leaf<Bitcoin::integer>;
    using Dpubkey = leaf<secp256k1::pubkey>;
    using Dsecret = leaf<secp256k1::secret>;
    using Dsat = leaf<Bitcoin::satoshi>;
    template <typename Y, typename ... X> using built_in_function = leaf<std::function<Y (X...)>>;

}

#endif

