#include <Diophant/built.in/hash.hpp>
#include <gigamonkey/hash.hpp>

namespace Diophant {
    data::bytes SHA1_128 (const data::bytes &m) {
        return data::crypto::SHA1 (m);
    }

    data::bytes SHA2_256 (const data::bytes &m) {
        return data::crypto::SHA2_256 (m);
    }

    data::bytes SHA3_256 (const data::bytes &m) {
        return data::crypto::SHA3_256 (m);
    }

    data::bytes RIPEMD_160 (const data::bytes &m) {
        return data::crypto::RIPEMD_160 (m);
    }

    data::bytes Hash256 (const data::bytes &m) {
        return data::crypto::Bitcoin_256 (m);
    }

    data::bytes Hash160 (const data::bytes &m) {
        return data::crypto::Bitcoin_160 (m);
    }

    data::bytes Hash160 (const secp256k1::pubkey &m) {
        return data::crypto::Bitcoin_160 (m);
    }

    data::bytes SHA1_128 (const data::string &m) {
        return data::crypto::SHA1 (m);
    }

    data::bytes SHA2_256 (const data::string &m) {
        return data::crypto::SHA2_256 (m);
    }

    data::bytes SHA3_256 (const data::string &m) {
        return data::crypto::SHA3_256 (m);
    }

    data::bytes RIPEMD_160 (const data::string &m) {
        return data::crypto::RIPEMD_160 (m);
    }

    data::bytes Hash256 (const data::string &m) {
        return data::crypto::Bitcoin_256 (m);
    }

    data::bytes Hash160 (const data::string &m) {
        return data::crypto::Bitcoin_160 (m);
    }
}

