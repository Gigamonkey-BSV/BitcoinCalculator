#include <parse.hpp>
#include <tao/pegtl.hpp>

#include <gigamonkey/secp256k1.hpp>
#include <gigamonkey/numbers.hpp>

namespace Diophant {

    namespace parse {
        using namespace tao::pegtl;

        // comments are c++ style
        struct comment : sor<
        seq<string<'/','*'>, star<seq<not_at<string<'*','/'>>, ascii::print>>, string<'*','/'>>,
        seq<string<'/','/'>, star<seq<not_at<one<'\n'>>, ascii::print>>, one<'\n'>>> {};
        struct white : sor<one<' '>, one<'\t'>, one<'\n'>, comment> {};
        struct ws : star<white> {};

        // a decimal lit is 0 by itself or the digits 1 through 9 followed by digits.
        struct dec_lit : sor<one<'0'>, seq<range<'1', '9'>, star<digit>>> {};

        struct hex_digit : seq<xdigit, xdigit> {};
        struct hex_lit : seq<string<'0', 'x'>, star<hex_digit>> {};
        struct pubkey_lit : seq<one<'0'>, sor<one<'2'>, one<'3'>, one<'4'>>, star<hex_digit>> {};

        struct hex_string : seq<one<'\''>, star<hex_digit>, one<'\''>> {};

        // strings can have escaped characters with \ .
        struct string_body : star<sor<
        seq<not_at<sor<one<'\\'>, one<'"'>>>, ascii::print>,  // any ascii character other than \ and "
        seq<one<'\\'>, ascii::print>                          // \ followed by any printable character.
        >> {};

        // strings are written with ""
        struct string_lit : seq<
        one<'"'>,                                             // opening "
        string_body,
        one<'"'>> {};                                         // closing "

        // symbols are alpha characters followed by _ and alphanumeric.
        struct reserved_words : sor<
        string<'i', 'f'>,
        string<'i', 'n'>,
        string<'a', 's'>,
        string<'i', 's'>,
        string<'l', 'e', 't'>,
        string<'t', 'h', 'e', 'n'>,
        string<'e', 'l', 's', 'e'>,
        string<'w', 'i', 't', 'h'>,
        string<'g', 'i', 'v', 'e', 'n'>> {};

        struct symbol_char : sor<alnum, one<'_'>> {};

        struct symbol : minus<seq<alpha, star<symbol_char>>, reserved_words> {};

        struct expression;

        struct dif : seq<string<'i', 'f'>, not_at<symbol_char>, ws, expression, ws,
        string<'t', 'h', 'e', 'n'>, not_at<symbol_char>, ws, expression, ws,
        string<'e', 'l', 's', 'e'>, not_at<symbol_char>, ws, expression> {};

        struct lambda_start : one<'@'> {};
        struct lambda_arrow : string<'-','>'> {};
        struct lambda : seq<lambda_start, ws, plus<seq<symbol, ws>>, lambda_arrow, ws, expression> {};

        struct open_list : one<'['> {};
        struct close_list : one<']'> {};
        struct list : seq<open_list,
        opt<seq<ws, expression, ws, star<seq<one<','>, ws, expression, ws>>>>,
        close_list> {};

        struct open_paren : one<'('> {};
        struct close_paren : one<')'> {};

        struct parenthetical : seq<open_paren, ws, expression, ws, star<seq<one<','>>, ws, expression, ws>, close_paren> {};

        struct atom : sor<dec_lit, hex_lit, pubkey_lit, hex_string, string_lit, symbol,
        dif, symbol, parenthetical, list, lambda> {};

        struct call : seq<plus<white>, atom> {};
        struct call_expr : seq<atom, star<call>> {};

        struct unary_operator : sor<one<'-'>, one<'!'>, one<'~'>, one<'+'>, one<'*'>> {};

        struct unary_expr;
        struct unary_operation : seq<unary_operator, unary_expr> {};
        struct unary_expr : sor<unary_operation, call_expr> {};

        struct pow_expr;
        struct mul_expr;
        struct mod_expr;
        struct div_mod_expr;
        struct div_expr;
        struct sub_expr;
        struct add_expr;

        struct pow_op : seq<ws, one<'^'>, ws, pow_expr> {};
        struct mul_op : seq<ws, sor<one<'*'>, one<'%'>, one<'~'>>, ws, mul_expr> {};
        struct mod_op : seq<ws, string<'%'>, ws, mod_expr> {};
        struct div_mod_op : seq<ws, string<'/', '%'>, ws, div_mod_expr> {};
        struct div_op : seq<ws, one<'/'>, ws, div_expr> {};
        struct sub_op : seq<ws, one<'-'>, ws, sub_expr> {};
        struct add_op : seq<ws, one<'+'>, ws, add_expr> {};

        struct pow_expr : seq<unary_expr, opt<pow_op>> {};
        struct mul_expr : seq<pow_expr, opt<mul_op>> {};
        struct mod_expr : seq<mul_expr, opt<mod_op>> {};
        struct div_mod_expr : seq<mod_expr, opt<div_mod_op>> {};
        struct div_expr : seq<div_mod_expr, opt<div_op>> {};
        struct sub_expr : seq<div_expr, opt<sub_op>> {};
        struct add_expr : seq<sub_expr, opt<add_op>> {};

        struct comp_expr;
        struct greater_equal_op : seq<ws, string<'>','='>, ws, comp_expr> {};
        struct less_equal_op : seq<ws, string<'<','='>, ws, comp_expr> {};
        struct greater_op : seq<ws, one<'>'>, ws, comp_expr> {};
        struct less_op : seq<ws, one<'<'>, ws, comp_expr> {};

        struct comp_expr : seq<add_expr,
        opt<sor<greater_equal_op, less_equal_op, greater_op, less_op>>> {};

        struct bool_equal_expr;

        struct bool_equal_op : seq<ws, string<'=','='>, ws, bool_equal_expr> {};
        struct bool_unequal_op : seq<ws, string<'!','='>, ws, bool_equal_expr> {};

        struct bool_equal_expr : seq<comp_expr, opt<sor<bool_equal_op, bool_equal_op>>> {};
        struct bool_unequal_expr :
        seq<bool_equal_expr, opt<sor<bool_equal_op, bool_unequal_op>>> {};

        struct bool_and_expr;
        struct bool_or_expr;

        struct bool_and_op : seq<ws, string<'&','&'>, ws, bool_and_expr> {};
        struct bool_or_op : seq<ws, string<'|','|'>, ws, bool_or_expr> {};

        struct bool_and_expr : seq<bool_unequal_expr, opt<bool_and_op>> {};
        struct bool_or_expr : seq<bool_and_expr, opt<bool_or_op>> {};

        struct expression : seq<bool_or_expr> {};

    }

    struct parser {
        void read_dec_literal (data::slice<char>);
        void read_sats_literal (data::slice<char>);
        void read_hexidecimal_literal (data::slice<char>);
        void read_hex_literal (data::slice<char>);
        void read_pubkey_literal (data::slice<char>);

        void call ();

        void unary (unary_operator op);
        void binary (binary_operator op);

        bool valid ();

        expression top ();
    };

    namespace rules {
        namespace pegtl = tao::pegtl;

        template <typename Rule> struct eval_action : pegtl::nothing<Rule> {};

        template <> struct eval_action<parse::expression> {
            template <typename Input>
            static void apply (const Input &in, parser &eval);
        };

        template <> struct eval_action<parse::bool_or_expr> {
            template <typename Input>
            static void apply (const Input &in, parser &eval);
        };

        template <> struct eval_action<parse::bool_and_expr> {
            template <typename Input>
            static void apply (const Input &in, parser &eval);
        };

        template <> struct eval_action<parse::bool_unequal_expr> {
            template <typename Input>
            static void apply (const Input &in, parser &eval);
        };

        template <> struct eval_action<parse::bool_equal_expr> {
            template <typename Input>
            static void apply (const Input &in, parser &eval);
        };

        template <> struct eval_action<parse::comp_expr> {
            template <typename Input>
            static void apply (const Input &in, parser &eval);
        };

    }

    template <typename T> struct leaf : node {
        T Value;
    };

    parser read_line (parser p, const std::string &in) {
        if (!tao::pegtl::parse<parse::expression, rules::eval_action> (tao::pegtl::memory_input<> {in, "expression"}, p))
            throw exception {} << "could not parse line \"" << in << "\"";
            return p;
    }

}
