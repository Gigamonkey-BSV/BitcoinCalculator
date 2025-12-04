#ifndef BITCOIN_CALCULATOR_PARSE_BASE64
#define BITCOIN_CALCULATOR_PARSE_BASE64

#include <tao/pegtl.hpp>

namespace tao_pegtl_grammar {
    using namespace tao::pegtl;

    // Base64 single character
    using base64_char =
        sor<
            ranges<'A','Z','a','z'>,
            range<'0','9'>,
            one<'+','/'>>;

    // Base64 padding '='
    using base64_pad = one<'='>;

    using base64_quad = seq<base64_char, base64_char, base64_char, base64_char>;

    using base64_close =
        sor<seq<base64_char, base64_char, base64_char, base64_pad>,
            seq<base64_char, base64_char, base64_pad, base64_pad>>;

    struct base64 : seq<star<base64_quad>, opt<base64_close>> {};

}

#endif
