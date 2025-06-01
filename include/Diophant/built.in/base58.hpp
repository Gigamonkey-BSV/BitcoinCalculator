#ifndef BITCOIN_CALCULATOR_BUILTIN_BASE58
#define BITCOIN_CALCULATOR_BUILTIN_BASE58

#include <Diophant/built.in/string.hpp>

namespace Diophant {

    // base 58
    data::N decode_base_58 (const data::string &x);
    data::string encode_base_58 (const data::N &x);

    std::tuple<data::byte, data::bytes> decode_base_58_check (const data::string &x);
    data::string encode_base_58_check (const data::byte &, const data::bytes &);

}

#endif

