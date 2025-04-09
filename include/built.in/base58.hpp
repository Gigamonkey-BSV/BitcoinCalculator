#ifndef BITCOIN_CALCULATOR_BUILTIN_BASE58
#define BITCOIN_CALCULATOR_BUILTIN_BASE58

#include <built.in/string.hpp>

namespace Diophant {

    // base 58
    uint256 decode_base_58 (const data::string &x);
    data::string encode_base_58 (const uint256 &x);

    std::tuple<data::byte, Bitcoin::integer> decode_base_58_check (const data::string &x);
    data::string encode_base_58_check (const data::byte &, const Bitcoin::integer &);

}

#endif

