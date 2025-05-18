#ifndef BITCOIN_CALCULATOR_BUILTIN_BASE58
#define BITCOIN_CALCULATOR_BUILTIN_BASE58

#include <Diophant/built.in/string.hpp>

namespace Diophant {

    // base 58
    data::uint256_little decode_base_58 (const data::string &x);
    data::string encode_base_58 (const data::uint256_little &x);

    std::tuple<data::byte, Bitcoin::integer> decode_base_58_check (const data::string &x);
    data::string encode_base_58_check (const data::byte &, const Bitcoin::integer &);

}

#endif

