#ifndef BITCOIN_CALCULATOR_BUILTIN_BASE58
#define BITCOIN_CALCULATOR_BUILTIN_BASE58

#include <data/tuple.hpp>
#include <Diophant/built.in/string.hpp>

namespace Diophant {

    // base 58
    data::N decode_base_58 (const data::string &x);
    data::string encode_base_58 (const data::N &x);

    data::tuple<data::byte, data::bytes> decode_base_58_check (const data::string &x);
    data::string encode_base_58_check (const data::byte &, const data::bytes &);

    data::string address_encode (const data::bytes &, Bitcoin::net = Bitcoin::net::Main);
    data::tuple<data::bytes, Bitcoin::net> address_decode (const data::string &);

    data::string WIF_encode (const data::N &, Bitcoin::net = Bitcoin::net::Main, bool compressed = true);
    data::tuple<data::N, Bitcoin::net, bool> WIF_decode (const data::string &);

    data::bytes sign_with_WIF (const data::string &wif, const data::bytes &digest);

}

#endif

