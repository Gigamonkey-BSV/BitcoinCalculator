#ifndef BITCOIN_CALCULATOR_PARSE_WHITESPACE
#define BITCOIN_CALCULATOR_PARSE_WHITESPACE

#include <tao/pegtl.hpp>

namespace tao_pegtl_grammar {
    using namespace tao::pegtl;

    // comments are c++ style
    struct comment : sor<
        seq<string<'/','*'>, star<seq<not_at<string<'*','/'>>, ascii::print>>, string<'*','/'>>,
        seq<string<'/','/'>, star<seq<not_at<one<'\n'>>, ascii::print>>, one<'\n'>>> {};

    struct white : sor<one<' '>, one<'\t'>, one<'\n'>, comment> {};
    struct ws : star<white> {};
    struct rs : plus<white> {};

}

#endif

