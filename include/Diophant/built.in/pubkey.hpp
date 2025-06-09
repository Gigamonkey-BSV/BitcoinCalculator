#ifndef BITCOIN_CALCULATOR_BUILTIN_PUBKEY
#define BITCOIN_CALCULATOR_BUILTIN_PUBKEY

#include <Diophant/built.in/modular.hpp>

namespace Diophant {

    bool pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    bool pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    bool pubkey_unequal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);

    bool pubkey_valid (const secp256k1::pubkey &x);

    secp256k1::pubkey secret_to_public (bool, const data::N &x);

    bool pubkey_compressed (const secp256k1::pubkey &x);
    bool pubkey_uncompressed (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_compress (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_decompress (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const data::N &y);
    secp256k1::pubkey pubkey_times (const data::N x, const secp256k1::pubkey &y);

    data::uint160_little address_hash (const secp256k1::pubkey &);

    data::string address_from_pubkey (const secp256k1::pubkey &, bool mainnet = true);
    data::string address_from_secret (const data::N &, bool mainnet = true, bool compressed = true);

    data::string address_from_WIF (const data::string &);

    data::bytes sign (const data::N &key, const data::uint256_little &digest);
    bool verify (const secp256k1::pubkey &x, const data::uint256_little &digest, const data::bytes &sig);

    data::bytes sign_with_WIF (const data::string &wif, const data::uint256_little &digest);

}

#endif
