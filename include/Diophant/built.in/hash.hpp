#ifndef BITCOIN_CALCULATOR_BUILTIN_HASH
#define BITCOIN_CALCULATOR_BUILTIN_HASH

#include <Diophant/built.in/pubkey.hpp>

namespace Diophant {
    data::uint128_little SHA1_256 (const data::bytes &m);

    data::uint256_little SHA2_256 (const data::bytes &m);

    data::uint256_little SHA3_256 (const data::bytes &m);

    data::uint160_little RIPMD160 (const data::bytes &m);

    data::uint256_little Hash256 (const data::bytes &m);

    data::uint160_little Hash160 (const data::bytes &m);

}

#endif

