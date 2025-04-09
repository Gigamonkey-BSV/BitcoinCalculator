#ifndef BITCOIN_CALCULATOR_BUILTIN_HASH
#define BITCOIN_CALCULATOR_BUILTIN_HASH

#include <built.in/pubkey.hpp>

namespace Diophant {

    uint256 SHA2_256 (const Bitcoin::integer &key);
    uint256 SHA2_256 (const data::string &key);
    uint256 SHA3_256 (const Bitcoin::integer &key);
    uint256 SHA3_256 (const data::string &key);
    uint256 Hash256 (const Bitcoin::integer &key);
    uint256 Hash256 (const data::string &key);

    Bitcoin::integer Hash160 (const Bitcoin::integer &key);
    Bitcoin::integer Hash160 (const data::string &key);
    Bitcoin::integer Hash160 (const secp256k1::pubkey &);

}

#endif

