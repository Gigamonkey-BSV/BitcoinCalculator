#ifndef BITCOIN_CALCULATOR_BUILTIN_PUBKEY
#define BITCOIN_CALCULATOR_BUILTIN_PUBKEY

#include <Diophant/built.in/modular.hpp>

namespace Diophant {

    bool pubkey_equal (const data::bytes &x, const data::bytes &y);

    bool pubkey_valid (const data::bytes &x);

    data::bytes secret_to_public (bool, const data::N &x);
    data::bytes WIF_to_public (const data::string &x);

    bool pubkey_compressed (const data::bytes &x);
    bool pubkey_uncompressed (const data::bytes &x);

    data::bytes pubkey_compress (const data::bytes &x);
    data::bytes pubkey_decompress (const data::bytes &x);

    data::bytes pubkey_negate (const data::bytes &x);
    data::bytes pubkey_plus (const data::bytes &x, const data::bytes &y);
    data::bytes pubkey_times (const data::bytes &x, const data::N &y);
    data::bytes pubkey_times (const data::N x, const data::bytes &y);

    data::uint160_little address_hash (const data::bytes &);

    data::string address_from_pubkey (const data::bytes &, Bitcoin::net = Bitcoin::net::Main);
    data::string address_from_secret (const data::N &, Bitcoin::net = Bitcoin::net::Main, bool compressed = true);

    data::string address_from_WIF (const data::string &);

    data::bytes sign (const data::N &key, const data::bytes &digest);
    bool verify (const data::bytes &x, const data::bytes &digest, const data::bytes &sig);

    data::bytes cast_pubkey_to_bytes (const data::bytes &);

}

#endif
