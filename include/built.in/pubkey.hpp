#ifndef BITCOIN_CALCULATOR_BUILTIN_PUBKEY
#define BITCOIN_CALCULATOR_BUILTIN_PUBKEY

#include <built.in/modular.hpp>

namespace Diophant {

    Bitcoin::integer pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    Bitcoin::integer pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    Bitcoin::integer pubkey_unequal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);

    Bitcoin::integer pubkey_valid (const secp256k1::pubkey &x);

    secp256k1::pubkey secret_to_public (const uint256 &x, const Bitcoin::integer &);

    Bitcoin::integer pubkey_compressed (const secp256k1::pubkey &x);
    Bitcoin::integer pubkey_uncompressed (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_compress (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_decompress (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const uint256 &y);
    secp256k1::pubkey pubkey_times (const uint256 &x, const secp256k1::pubkey &y);

    Bitcoin::integer Hash160 (const secp256k1::pubkey &);

}

#endif
