#ifndef BITCOIN_CALCULATOR_BUILTIN_HASH
#define BITCOIN_CALCULATOR_BUILTIN_HASH

#include <Diophant/built.in/pubkey.hpp>

namespace Diophant {
    data::uint128_little SHA1_128 (const data::bytes &m);

    data::uint256_little SHA2_256 (const data::bytes &m);

    data::uint256_little SHA3_256 (const data::bytes &m);

    data::uint160_little RIPEMD_160 (const data::bytes &m);

    data::uint256_little Hash256 (const data::bytes &m);

    data::uint160_little Hash160 (const data::bytes &m);

    data::uint128_little SHA1_128 (const data::string &m);

    data::uint256_little SHA2_256 (const data::string &m);

    data::uint256_little SHA3_256 (const data::string &m);

    data::uint160_little RIPEMD_160 (const data::string &m);

    data::uint256_little Hash256 (const data::string &m);

    data::uint160_little Hash160 (const data::string &m);

    data::uint160_little Hash160 (const secp256k1::pubkey &m);

}

#endif

