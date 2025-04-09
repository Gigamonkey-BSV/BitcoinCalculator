#include <built.in/base58.hpp>
#include <gigamonkey/hash.hpp>

namespace Diophant {

    uint256 SHA2_256 (const Bitcoin::integer &key) {
        return data::crypto::SHA2_256 (key);
    }

    uint256 SHA2_256 (const data::string &key) {
        return data::crypto::SHA2_256 (key);
    }

    uint256 SHA3_256 (const Bitcoin::integer &key) {
        return data::crypto::SHA3_256 (key);
    }

    uint256 SHA3_256 (const data::string &key) {
        return data::crypto::SHA3_256 (key);
    }

    uint256 Hash256 (const Bitcoin::integer &key) {
        return data::crypto::Bitcoin_256 (key);
    }

    uint256 Hash256 (const data::string &key) {
        return data::crypto::Bitcoin_256 (key);
    }

    Bitcoin::integer Hash160 (const Bitcoin::integer &key) {
        return Bitcoin::integer::read (data::crypto::Bitcoin_160 (key));
    }

    Bitcoin::integer Hash160 (const data::string &key) {
        return Bitcoin::integer::read (data::crypto::Bitcoin_160 (key));
    }

    Bitcoin::integer Hash160 (const secp256k1::pubkey &key) {
        return Bitcoin::integer::read (data::crypto::Bitcoin_160 (key));
    }

}

