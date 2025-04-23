#ifndef BITCOIN_CALCULATOR_BUILTIN_PUBKEY
#define BITCOIN_CALCULATOR_BUILTIN_PUBKEY

#include <built.in/modular.hpp>

namespace Diophant {

    bool pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    bool pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    bool pubkey_unequal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);

    bool pubkey_valid (const secp256k1::pubkey &x);

    secp256k1::pubkey secret_to_public (bool, const uint256 &x);

    bool pubkey_compressed (const secp256k1::pubkey &x);
    bool pubkey_uncompressed (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_compress (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_decompress (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const uint256 &y);
    secp256k1::pubkey pubkey_times (const uint256 &x, const secp256k1::pubkey &y);

    Bitcoin::integer Hash160 (const secp256k1::pubkey &);

}

#endif
