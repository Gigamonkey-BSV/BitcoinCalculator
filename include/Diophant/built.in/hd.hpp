#ifndef BITCOIN_CALCULATOR_BUILTIN_HD
#define BITCOIN_CALCULATOR_BUILTIN_HD

#include <data/tuple.hpp>
#include <Diophant/built.in/pubkey.hpp>

namespace Diophant {

    data::string encode_HD_pubkey (
        const data::bytes &,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence);

    data::string encode_HD_secret (
        const data::N &,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence);

    data::tuple<data::bytes, data::bytes, Bitcoin::net, data::N, data::N, data::N>
    decode_HD_pubkey (const data::string &);

    data::tuple<data::N, data::bytes, Bitcoin::net, data::N, data::N, data::N>
    decode_HD_secret (const data::string &);

    data::string HD_secret_to_public (const data::string &);

    data::tuple<data::bytes, data::bytes, Bitcoin::net, data::N, data::N, data::N>
    HD_secret_to_public (
        const data::N &,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence);

    data::string address_from_HD (const data::string &);

    data::tuple<data::bytes, Bitcoin::net> address_from_HD (
        const data::N &,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence);

    data::tuple<data::bytes, Bitcoin::net> address_from_HD (
        const data::bytes &,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence);

    data::string HD_pubkey_derive (const data::string &, const data::N &);
    data::string HD_secret_derive (const data::string &, const data::N &);
    data::string HD_secret_derive_hardened (const data::string &, const data::N &);

    data::bytes sign_with_HD (const data::string &xprv, const data::bytes &digest);
    bool verify_with_HD (const data::string &xpub, const data::bytes &digest, const data::bytes &sig);

}

#endif

