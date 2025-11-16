#ifndef BITCOIN_CALCULATOR_BUILTIN_HD
#define BITCOIN_CALCULATOR_BUILTIN_HD

#include <data/tuple.hpp>
#include <Diophant/built.in/pubkey.hpp>

namespace Diophant {

    data::string encode_HD_pubkey (
        const secp256k1::pubkey &,
        const data::bytes &chain_code,
        Bitcoin::net network,
        data::byte depth,
        data::uint32 parent,
        data::uint32 sequence);

    data::string encode_HD_secret (
        const data::N &,
        const data::bytes &chain_code,
        Bitcoin::net network,
        data::byte depth,
        data::uint32 parent,
        data::uint32 sequence);

    data::tuple<secp256k1::pubkey, data::bytes, Bitcoin::net, data::byte, data::uint32, data::uint32>
    decode_HD_pubkey (const std::string &);

    data::tuple<data::N, data::bytes, Bitcoin::net, data::byte, data::uint32, data::uint32>
    decode_HD_secret (const std::string &);

    data::bytes sign (const std::string &key, const data::uint256_little &digest);
    bool verify (const std::string &x, const data::uint256_little &digest, const data::bytes &sig);

    data::string hd_secret_to_public (const data::string &);
    data::string hd_pubkey_derive (const data::string &, data::list<data::uint32>);
    data::string hd_secret_derive (const data::string &, data::list<data::uint32>);

}

#endif

