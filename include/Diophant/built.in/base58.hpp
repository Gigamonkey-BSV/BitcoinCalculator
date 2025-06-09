#ifndef BITCOIN_CALCULATOR_BUILTIN_BASE58
#define BITCOIN_CALCULATOR_BUILTIN_BASE58

#include <Diophant/built.in/string.hpp>

namespace Diophant {

    // base 58
    data::N decode_base_58 (const data::string &x);
    data::string encode_base_58 (const data::N &x);

    data::tuple<data::byte, data::bytes> decode_base_58_check (const data::string &x);
    data::string encode_base_58_check (const data::byte &, const data::bytes &);

    data::string address_encode (const data::uint160_little &, bool mainnet = true);
    data::string WIF_encode (const data::N &, bool mainnet = true, bool compressed = true);
    data::tuple<data::uint160_little, bool> address_decode (const data::string &);
    data::tuple<data::N, bool, bool> WIF_decode (const data::string &);

}

#endif

