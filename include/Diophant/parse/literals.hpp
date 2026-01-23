#ifndef BITCOIN_CALCULATOR_PARSE_LITERALS
#define BITCOIN_CALCULATOR_PARSE_LITERALS

#include "base58.hpp"
#include "base64.hpp"
#include "whitespace.hpp"

namespace tao_pegtl_grammar {

    // a decimal lit is 0 by itself, 0d followed by any number of digits 0 - 9,
    // or the digits 1 through 9 followed by digits.
    struct dec_number : sor<
        seq<one<'0'>, opt<seq<one<'d'>, star<digit>>>>,
        seq<range<'1', '9'>, star<digit>>> {};

    struct hex_digit : seq<xdigit, xdigit> {};

    struct two_hex_digits : seq<hex_digit, hex_digit> {};
    struct four_hex_digits : seq<two_hex_digits, two_hex_digits> {};
    struct eight_hex_digits : seq<four_hex_digits, four_hex_digits> {};
    struct sixteen_hex_digits : seq<eight_hex_digits, eight_hex_digits> {};
    struct thirty_two_hex_digits : seq<sixteen_hex_digits, sixteen_hex_digits> {};
    struct sixty_four_hex_digits : seq<thirty_two_hex_digits, thirty_two_hex_digits> {};

    struct base58_number : seq<one<'0'>, sor<one<'o'>, one<'1'>>, base58> {};

    struct hex_number : seq<string<'0', 'x'>, star<hex_digit>> {};

    struct number : sor<hex_number, dec_number, base58_number> {};

    struct unsigned_flag : sor<one<'u'>, one<'i'>> {};
    struct fixed_size_flag : number {};
    struct big_endian_flag : one<'b'> {};
    struct little_endian_flag : one<'l'> {};
    struct number_suffix : seq<one<'_'>, opt<unsigned_flag>, opt<sor<big_endian_flag, little_endian_flag>>, opt<fixed_size_flag>> {};

    struct number_lit : seq<number, opt<number_suffix>> {};

    struct pubkey_lit : seq<one<'0'>,
        sor<seq<sor<one<'2'>, one<'3'>>, thirty_two_hex_digits>,
        seq<one<'4'>, sixty_four_hex_digits>>> {};

    struct hex_encoding : seq<string<'h','e','x'>, ws, one<':'>, star<seq<ws, hex_digit>>> {};
    struct base58_encoding : seq<string<'b','a','s','e','5','8'>, ws, one<':'>, star<ws, base58_char>> {};
    struct base64_encoding : seq<string<'b','a','s','e','6','4'>, ws, one<':'>, base64> {};

    struct bytes_lit : sor<
        seq<one<'`'>, star<hex_digit>, one<'`'>>,
        seq<one<'#'>, sor<star<hex_digit>, seq<one<'<'>, sor<hex_encoding, base58_encoding, base64_encoding>, one<'>'>>>>> {};

    // strings can have escaped characters with \ .
    struct string_body : star<sor<
        seq<not_at<sor<one<'\\'>, one<'"'>>>, ascii::print>,  // any ascii character other than \ and "
        seq<one<'\\'>, ascii::print>>> {};                    // \ followed by any printable character.

    // strings are written with ""
    struct string_lit : seq<
        one<'"'>,                                             // opening "
        string_body,
        one<'"'>> {};                                         // closing "

}

#endif

