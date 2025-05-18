#ifndef BITCOIN_CALCULATOR_BUILTIN_PUBKEY
#define BITCOIN_CALCULATOR_BUILTIN_PUBKEY

#include <Diophant/built.in/modular.hpp>

namespace Diophant {

    bool pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    bool pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    bool pubkey_unequal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);

    bool pubkey_valid (const secp256k1::pubkey &x);

    secp256k1::pubkey secret_to_public (bool, const data::uint256_little &x);

    bool pubkey_compressed (const secp256k1::pubkey &x);
    bool pubkey_uncompressed (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_compress (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_decompress (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const data::uint256_little &y);
    secp256k1::pubkey pubkey_times (const data::uint256_little &x, const secp256k1::pubkey &y);

}

#endif
