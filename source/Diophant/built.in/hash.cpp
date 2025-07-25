#include <Diophant/built.in/hash.hpp>
#include <gigamonkey/hash.hpp>

namespace Diophant {
    data::uint128_little SHA1_128 (const data::bytes &m) {
        return data::crypto::SHA1 (m);
    }

    data::uint256_little SHA2_256 (const data::bytes &m) {
        return data::crypto::SHA2_256 (m);
    }

    data::uint256_little SHA3_256 (const data::bytes &m) {
        return data::crypto::SHA3_256 (m);
    }

    data::uint160_little RIPEMD_160 (const data::bytes &m) {
        return data::crypto::RIPEMD_160 (m);
    }

    data::uint256_little Hash256 (const data::bytes &m) {
        return data::crypto::Bitcoin_256 (m);
    }

    data::uint160_little Hash160 (const data::bytes &m) {
        return data::crypto::Bitcoin_160 (m);
    }

    data::uint160_little Hash160 (const secp256k1::pubkey &m) {
        return data::crypto::Bitcoin_160 (m);
    }

    data::uint128_little SHA1_128 (const data::string &m) {
        return data::crypto::SHA1 (m);
    }

    data::uint256_little SHA2_256 (const data::string &m) {
        return data::crypto::SHA2_256 (m);
    }

    data::uint256_little SHA3_256 (const data::string &m) {
        return data::crypto::SHA3_256 (m);
    }

    data::uint160_little RIPEMD_160 (const data::string &m) {
        return data::crypto::RIPEMD_160 (m);
    }

    data::uint256_little Hash256 (const data::string &m) {
        return data::crypto::Bitcoin_256 (m);
    }

    data::uint160_little Hash160 (const data::string &m) {
        return data::crypto::Bitcoin_160 (m);
    }
}

