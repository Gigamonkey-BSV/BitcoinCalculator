#ifndef BITCOIN_CALCULATOR_PARSE_TAO
#define BITCOIN_CALCULATOR_PARSE_TAO

#include <tao/pegtl.hpp>

namespace tao_pegtl_grammar {
    using namespace tao::pegtl;

    // comments are c++ style
    struct comment : sor<
        seq<string<'/','*'>, star<seq<not_at<string<'*','/'>>, ascii::print>>, string<'*','/'>>,
        seq<string<'/','/'>, star<seq<not_at<one<'\n'>>, ascii::print>>, one<'\n'>>> {};

    struct white : sor<one<' '>, one<'\t'>, one<'\n'>, comment> {};
    struct ws : star<sor<white, comment>> {};

    // the overall structure of a program.
    struct statement;
    struct object;

    struct program : seq<ws, star<seq<statement, ws>>, object> {};

    struct declaration;
    struct definition;

    struct statement : sor<definition, declaration> {};

    struct subject;

    struct declaration : seq<subject, ws, one<';'>> {};

    struct predicate;
    struct definition : seq<subject, ws, predicate, ws, one<';'>> {};

    struct predicate : seq<string<':','='>, object> {};

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
        seq<one<'\\'>, ascii::print>>> {};                    // \ followed by any printable character.

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
        string<'o', 'r'>,
        string<'a', 'n', 'd'>,
        string<'l', 'e', 't'>,
        string<'t', 'h', 'e', 'n'>,
        string<'e', 'l', 's', 'e'>,
        string<'w', 'i', 't', 'h'>,
        string<'g', 'i', 'v', 'e', 'n'>,
        string<'l', 'a', 'm', 'b', 'd', 'a'>> {};

    struct symbol_char : sor<alnum, one<'_'>> {};

    struct symbol : minus<seq<alnum, star<symbol_char>>, reserved_words> {};
    struct var : seq<one<'_'>, opt<symbol>> {};

    // used inside lambdas
    struct anon_var : seq<one<'_'>, opt<dec_lit>> {};

    template <typename atom> struct expression;

    struct arrow : string<'-','>'> {};

    struct lambda_start : one<'@'> {};
    template <typename atom> struct lambda_body;
    struct lambda_symbol : symbol {};
    template <typename atom> struct lambda : seq<lambda_start, ws,
        sor<seq<lambda_symbol, star<seq<plus<white>, lambda_symbol>>, ws, arrow, ws, lambda_body<atom>>, lambda_body<sor<anon_var, atom>>>> {};

    template <typename atom> struct dif : seq<string<'i', 'f'>, not_at<symbol_char>, ws, expression<atom>, ws,
        string<'t', 'h', 'e', 'n'>, not_at<symbol_char>, ws, expression<atom>, ws,
        string<'e', 'l', 's', 'e'>, not_at<symbol_char>, ws, lambda_body<atom>> {};

    struct comma : one<','> {};
    template <typename elem> struct sequence : seq<elem, star<seq<ws, comma, ws, elem>>> {};
    template <typename elem> struct empty_sequence : seq<ws, opt<seq<sequence<elem>, ws>>> {};

    struct open_paren : one<'('> {};
    struct close_paren : one<')'> {};
    template <typename atom> struct parenthetical : seq<open_paren, empty_sequence<expression<atom>>, close_paren> {};

    struct open_list : one<'['> {};
    struct close_list : one<']'> {};
    template <typename atom> struct list : seq<open_list, empty_sequence<expression<atom>>, close_list> {};

    struct rule_symbol : symbol {};
    template <typename atom> struct rule : seq<rule_symbol, ws, arrow, ws, expression<atom>> {};
    struct let_open : seq<string<'l', 'e', 't'>, not_at<symbol_char>> {};
    struct let_in : seq<string<'i','n'>, not_at<symbol_char>> {};
    template <typename atom> struct let : seq<let_open, ws, sequence<rule<atom>>, ws, let_in, ws, lambda_body<atom>> {};

    struct open_struct : one<'{'> {};
    struct close_struct : one<'}'> {};
    template <typename atom> struct dstruct : seq<open_struct, empty_sequence<rule<atom>>, close_struct> {};

    struct left_unary_operand : sor<one<'-'>, one<'~'>, one<'!'>, one<'+'>, one<'*'>, one<'$'>> {};
    struct right_unary_operand : sor<one<'!'>> {};

    template <typename atom> struct call_op : seq<plus<white>, atom> {};
    template <typename atom> struct call_expr : seq<atom, star<call_op<atom>>> {};

    template <typename atom> struct left_unary_expr;
    template <typename atom> struct left_unary_operation : seq<left_unary_operand, ws, left_unary_expr<atom>> {};
    template <typename atom> struct left_unary_expr : sor<left_unary_operation<atom>, call_expr<atom>> {};

    //template <typename atom> struct dot_expr;
    template <typename atom> struct dot_op : seq<ws, one<'.'>, ws, left_unary_expr<atom>> {};
    template <typename atom> struct dot_expr : seq<left_unary_expr<atom>, star<dot_op<atom>>> {};

    template <typename atom> struct cat_expr;
    template <typename atom> struct cat_op : seq<ws, string<'<','>'>, ws, cat_expr<atom>> {};
    template <typename atom> struct cat_expr : seq<dot_expr<atom>, opt<cat_op<atom>>> {};

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

    template <typename atom> struct pow_expr : seq<cat_expr<atom>, opt<pow_op<atom>>> {};
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

    template <typename atom> struct identical_expr;
    template <typename atom> struct identical_op : seq<ws, string<'=','=','='>, ws, identical_expr<atom>> {};
    template <typename atom> struct identical_expr : seq<bool_or_expr<atom>, opt<identical_op<atom>>> {};

    template <typename atom> struct lambda_body : identical_expr<atom> {};

    template <typename atom> struct apply_expr;
    template <typename atom> struct apply_op : seq<ws, one<'$'>, ws, apply_expr<atom>> {};
    template <typename atom> struct apply_expr : seq<identical_expr<atom>, opt<apply_op<atom>>> {};

    struct atom : sor<hex_lit, pubkey_lit, dec_lit, hex_string_lit, string_lit, symbol,
        dif<atom>, parenthetical<atom>, list<atom>, let<atom>, lambda<atom>, dstruct<atom>> {};

    struct value : apply_expr<atom> {};

    // a pattern atom
    struct pattom : sor<hex_lit, pubkey_lit, dec_lit, hex_string_lit, string_lit, symbol, var,
        dif<pattom>, parenthetical<pattom>, list<pattom>, let<pattom>, lambda<pattom>, dstruct<atom>> {};

    template <typename atom> struct element_expr;
    template <typename atom> struct element_op :
        seq<ws, sor<string<'-',':'>,
            seq<string<'i', 's'>, not_at<symbol_char>>>, ws, element_expr<atom>> {};

    template <typename atom> struct element_expr : seq<apply_expr<atom>, opt<element_op<atom>>> {};

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

    struct type : intuitionistic_implies_expr<atom> {};

    struct cast_op : seq<ws, one<':'>, ws, apply_expr<atom>> {};
    template <typename atom> struct cast_expr : seq<type, opt<cast_op>> {};

    template <typename atom> struct expression : cast_expr<atom> {};

    struct object : expression<atom> {};

    struct pattern : expression<pattom> {};

    struct such_that_expr;
    struct such_that_op : seq<ws, string<'/',';'>, ws, such_that_expr> {};
    struct such_that_expr : seq<pattern, opt<such_that_op>> {};

    struct subject : such_that_expr {};


}

#endif
