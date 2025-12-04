#ifndef BITCOIN_CALCULATOR_PARSE_BASE58
#define BITCOIN_CALCULATOR_PARSE_BASE58

#include <tao/pegtl.hpp>

namespace tao_pegtl_grammar {
    using namespace tao::pegtl;

    using base58_char = sor<
        ranges<'1', '9'>,                       // 1-9
        ranges<'A', 'H'>,                       // A-H
        ranges<'J', 'N'>,                       // J-N
        ranges<'P', 'Z'>,                       // P-Z
        ranges<'a', 'k'>,                       // a-k
        ranges<'m', 'z'>>;                      // m-z

    struct base58 : star<base58_char> {};

}

#endif
