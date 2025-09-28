#ifndef BITCOIN_CALCULATOR_BUILTIN_HASH
#define BITCOIN_CALCULATOR_BUILTIN_HASH

#include <Diophant/built.in/pubkey.hpp>

namespace Diophant {
    data::bytes SHA1_128 (const data::bytes &m);

    data::bytes SHA2_256 (const data::bytes &m);

    data::bytes SHA3_256 (const data::bytes &m);

    data::bytes RIPEMD_160 (const data::bytes &m);

    data::bytes Hash256 (const data::bytes &m);

    data::bytes Hash160 (const data::bytes &m);

    data::bytes SHA1_128 (const data::string &m);

    data::bytes SHA2_256 (const data::string &m);

    data::bytes SHA3_256 (const data::string &m);

    data::bytes RIPEMD_160 (const data::string &m);

    data::bytes Hash256 (const data::string &m);

    data::bytes Hash160 (const data::string &m);

    data::bytes Hash160 (const secp256k1::pubkey &m);

}

#endif

