#include <parse.hpp>
#include <value.hpp>
#include <operators.hpp>
#include <tao/pegtl.hpp>

#include <gigamonkey/secp256k1.hpp>
#include <gigamonkey/numbers.hpp>


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

    struct two_hex_digits : seq<hex_digit, hex_digit> {};
    struct four_hex_digits : seq<two_hex_digits, two_hex_digits> {};
    struct eight_hex_digits : seq<four_hex_digits, four_hex_digits> {};
    struct sixteen_hex_digits : seq<eight_hex_digits, eight_hex_digits> {};
    struct thirty_two_hex_digits : seq<sixteen_hex_digits, sixteen_hex_digits> {};
    struct sixty_four_hex_digits : seq<thirty_two_hex_digits, thirty_two_hex_digits> {};

    struct hex_lit : seq<string<'0', 'x'>, star<hex_digit>> {};
    struct pubkey_lit : seq<one<'0'>,
        sor<seq<sor<one<'2'>, one<'3'>>, thirty_two_hex_digits>,
        seq<one<'4'>, sixty_four_hex_digits>>> {};

    struct hex_string_lit : seq<one<'\''>, star<hex_digit>, one<'\''>> {};

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

    struct symbol : minus<star<symbol_char>, reserved_words> {};

    struct expression;

    struct definition : seq<symbol, ws, one<'='>, ws, expression> {};

    struct let_open : seq<string<'l', 'e', 't'>, not_at<symbol_char>> {};
    struct let_in : seq<string<'i','n'>, not_at<symbol_char>> {};
    struct let : seq<let_open, ws, definition, star<seq<ws, one<','>, ws, definition>>, ws, let_in, ws, expression> {};

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

    struct var : seq<opt<symbol>, one<'.'>> {};
    struct typed_var : seq<opt<symbol>, ws, one<':'>, ws, expression> {};

    struct expression_atom : sor<dec_lit, hex_lit, pubkey_lit, hex_string_lit, string_lit, symbol,
        dif, parenthetical, list, let, lambda> {};

    struct pattern_atom : sor<dec_lit, hex_lit, pubkey_lit, hex_string_lit, string_lit, symbol,
        var, typed_var, dif, parenthetical, list, let, lambda> {};

    template <typename atom> struct call : seq<plus<white>, atom> {};
    template <typename atom> struct call_expr : seq<atom, star<call<atom>>> {};

    struct unary_operator : sor<one<'-'>, one<'!'>, one<'~'>, one<'+'>, one<'*'>> {};

    template <typename atom> struct unary_expr;
    template <typename atom> struct unary_operation : seq<unary_operator, unary_expr<atom>> {};
    template <typename atom> struct unary_expr : sor<unary_operation<atom>, call_expr<atom>> {};

    template <typename atom> struct pow_expr;
    template <typename atom> struct mul_expr;
    template <typename atom> struct mod_expr;
    template <typename atom> struct div_mod_expr;
    template <typename atom> struct div_expr;
    template <typename atom> struct sub_expr;
    template <typename atom> struct add_expr;

    template <typename atom> struct pow_op : seq<ws, one<'^'>, ws, pow_expr<atom>> {};
    template <typename atom> struct mul_op : seq<ws, sor<one<'*'>, one<'%'>, one<'~'>>, ws, mul_expr<atom>> {};
    template <typename atom> struct mod_op : seq<ws, string<'%'>, ws, mod_expr<atom>> {};
    template <typename atom> struct div_mod_op : seq<ws, string<'/', '%'>, ws, div_mod_expr<atom>> {};
    template <typename atom> struct div_op : seq<ws, one<'/'>, ws, div_expr<atom>> {};
    template <typename atom> struct sub_op : seq<ws, one<'-'>, ws, sub_expr<atom>> {};
    template <typename atom> struct add_op : seq<ws, one<'+'>, ws, add_expr<atom>> {};

    template <typename atom> struct pow_expr : seq<unary_expr<atom>, opt<pow_op<atom>>> {};
    template <typename atom> struct mul_expr : seq<pow_expr<atom>, opt<mul_op<atom>>> {};
    template <typename atom> struct mod_expr : seq<mul_expr<atom>, opt<mod_op<atom>>> {};
    template <typename atom> struct div_mod_expr : seq<mod_expr<atom>, opt<div_mod_op<atom>>> {};
    template <typename atom> struct div_expr : seq<div_mod_expr<atom>, opt<div_op<atom>>> {};
    template <typename atom> struct sub_expr : seq<div_expr<atom>, opt<sub_op<atom>>> {};
    template <typename atom> struct add_expr : seq<sub_expr<atom>, opt<add_op<atom>>> {};

    template <typename atom> struct comp_expr;
    template <typename atom> struct greater_equal_op : seq<ws, string<'>','='>, ws, comp_expr<atom>> {};
    template <typename atom> struct less_equal_op : seq<ws, string<'<','='>, ws, comp_expr<atom>> {};
    template <typename atom> struct greater_op : seq<ws, one<'>'>, ws, comp_expr<atom>> {};
    template <typename atom> struct less_op : seq<ws, one<'<'>, ws, comp_expr<atom>> {};

    template <typename atom> struct comp_expr : seq<add_expr<atom>,
        opt<sor<greater_equal_op<atom>, less_equal_op<atom>, greater_op<atom>, less_op<atom>>>> {};

    template <typename atom> struct bool_equal_expr;

    template <typename atom> struct bool_equal_op : seq<ws, string<'=','='>, ws, bool_equal_expr<atom>> {};
    template <typename atom> struct bool_unequal_op : seq<ws, string<'!','='>, ws, bool_equal_expr<atom>> {};

    template <typename atom> struct bool_equal_expr : seq<comp_expr<atom>, opt<sor<bool_equal_op<atom>, bool_equal_op<atom>>>> {};
    template <typename atom> struct bool_unequal_expr :
        seq<bool_equal_expr<atom>, opt<sor<bool_equal_op<atom>, bool_unequal_op<atom>>>> {};

    template <typename atom> struct bool_and_expr;
    template <typename atom> struct bool_or_expr;

    template <typename atom> struct bool_and_op : seq<ws, string<'&','&'>, ws, bool_and_expr<atom>> {};
    template <typename atom> struct bool_or_op : seq<ws, string<'|','|'>, ws, bool_or_expr<atom>> {};

    template <typename atom> struct bool_and_expr : seq<bool_unequal_expr<atom>, opt<bool_and_op<atom>>> {};
    template <typename atom> struct bool_or_expr : seq<bool_and_expr<atom>, opt<bool_or_op<atom>>> {};

    template <typename atom> struct element_op : seq<ws, string<':','-'>, ws, bool_or_expr<atom>> {};
    template <typename atom> struct element_expr : seq<bool_or_expr<atom>, opt<element_op<atom>>> {};

    template <typename atom> struct equal_expr;
    template <typename atom> struct unequal_expr;
    template <typename atom> struct double_implication_expr;

    template <typename atom> struct equal_op : seq<ws, one<'='>, ws, equal_expr<atom>> {};
    template <typename atom> struct unequal_op : seq<ws, string<'/', '='>, ws, unequal_expr<atom>> {};
    template <typename atom> struct double_implication_op : seq<ws, string<'<','=','=','>'>, ws, double_implication_expr<atom>> {};

    template <typename atom> struct equal_expr : seq<element_expr<atom>, opt<equal_op<atom>>> {};
    template <typename atom> struct unequal_expr : seq<equal_expr<atom>, opt<unequal_op<atom>>> {};
    template <typename atom> struct double_implication_expr : seq<unequal_expr<atom>, opt<double_implication_op<atom>>> {};

    template <typename atom> struct intuitionistic_and_expr;
    template <typename atom> struct intuitionistic_or_expr;
    template <typename atom> struct intuitionistic_implies_expr;

    template <typename atom> struct intuitionistic_and_op : seq<ws, one<'&'>, ws, intuitionistic_and_expr<atom>> {};
    template <typename atom> struct intuitionistic_or_op : seq<ws, one<'|'>, ws, intuitionistic_or_expr<atom>> {};
    template <typename atom> struct intuitionistic_implies_op :
    seq<ws, string<'=','>'>, ws, intuitionistic_implies_expr<atom>> {};

    template <typename atom> struct intuitionistic_and_expr : seq<double_implication_expr<atom>, opt<intuitionistic_and_op<atom>>> {};
    template <typename atom> struct intuitionistic_or_expr : seq<intuitionistic_and_expr<atom>, opt<intuitionistic_or_op<atom>>> {};
    template <typename atom> struct intuitionistic_implies_expr :
    seq<intuitionistic_or_expr<atom>, opt<intuitionistic_implies_op<atom>>> {};

    template <typename atom> struct such_that_expr;
    template <typename atom> struct such_that_op : seq<ws, string<'/',';'>, ws, intuitionistic_implies_expr<atom>> {};
    template <typename atom> struct such_that_expr : seq<intuitionistic_implies_expr<atom>, opt<such_that_op<atom>>> {};

    struct expression : seq<bool_or_expr<expression_atom>> {};

}

namespace Diophant {
    struct parser {
        void push (Expression);

        void call ();

        void unary (unary_operator op);
        void binary (binary_operator op);

        bool valid ();

        Expression top ();
    };

    namespace rules {
        namespace pegtl = tao::pegtl;

        template <typename Rule> struct eval_action : pegtl::nothing<Rule> {};

        template <> struct eval_action<parse::dec_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (secret::make (secp256k1::secret {uint256 {in.string_view ()}}));
            }
        };

        template <> struct eval_action<parse::hex_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                auto x = in.string_view ();
                eval.push (scriptnum::make (Bitcoin::integer {x.substr (2, x.size () - 2)}));
            }
        };

        template <> struct eval_action<parse::pubkey_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (pubkey::make (Bitcoin::pubkey {in.string_view ()}));
            }
        };

        template <> struct eval_action<parse::string_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                auto x = in.string_view ();
                eval.push (string::make (data::string {x.substr (1, x.size () - 2)}));
            }
        };

        template <> struct eval_action<parse::hex_string_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                auto x = in.string_view ();
                eval.push (scriptnum::make (Bitcoin::integer {x.substr (1, x.size () - 2)}));
            }
        };

        template <typename atom> struct eval_action<parse::unary_operation<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                // NOTE this won't work if we ever have any unary operators that are bigger than one char.
                eval.unary (unary_operator {*in.begin ()});
            }
        };

    }

    expression read_line (const std::string &in) {
        parser p;

        if (!tao::pegtl::parse<parse::expression, rules::eval_action> (tao::pegtl::memory_input<> {in, "expression"}, p))
            throw parse_error {in};
        return p.top ();
    }

}
