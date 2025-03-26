#include <machine.hpp>
#include <value.hpp>

namespace Diophant {

    // TODO
    // base 58 check encoding
    //   * addresses
    //   * wif
    // string split

    // both of these require structs and bytes.

    // string operations
    data::string string_cat (const data::string &x, const data::string &y);
    data::string string_left (const data::string &x, const Bitcoin::integer &y);
    data::string string_left (const data::string &x, const uint256 &y);
    data::string string_right (const data::string &x, const Bitcoin::integer &y);
    data::string string_right (const data::string &x, const uint256 &y);

    Bitcoin::integer scriptnum_cat (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const uint256 &y);
    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const uint256 &y);

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const uint256 &y);
    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const uint256 &y);

    // bool operations
    Bitcoin::integer scriptnum_bool_not (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_bool_and (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bool_or (const Bitcoin::integer &x, const Bitcoin::integer &y);

    // bit operations
    Bitcoin::integer scriptnum_bit_not (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_bit_and (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bit_xor (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bit_or (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_identical (const Bitcoin::integer &x, const Bitcoin::integer &y);

    // comparisons
    Bitcoin::integer scriptnum_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_unequal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_greater_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_less_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_greater (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_less (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer string_equal (const data::string &x, const data::string &y);
    Bitcoin::integer string_unequal (const data::string &x, const data::string &y);
    Bitcoin::integer scriptnum_greater_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_less_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_greater (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_less (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer secret_equal (const uint256 &x, const uint256 &y);
    Bitcoin::integer secret_unequal (const uint256 &x, const uint256 &y);
    Bitcoin::integer secret_greater_equal (const uint256 &x, const uint256 &y);
    Bitcoin::integer secret_less_equal (const uint256 &x, const uint256 &y);
    Bitcoin::integer secret_greater (const uint256 &x, const uint256 &y);
    Bitcoin::integer secret_less (const uint256 &x, const uint256 &y);

    Bitcoin::integer pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    Bitcoin::integer pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    Bitcoin::integer pubkey_unequal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);

    // size operations
    Bitcoin::integer scriptnum_size (const Bitcoin::integer &x);
    data::string string_size (const data::string &x);

    Bitcoin::integer scriptnum_minimal_size (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_minimal (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_is_minimal (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const uint256 &y);

    // arithmetic
    Bitcoin::integer scriptnum_negate (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_plus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_minus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_times (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_divide (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_mod (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer scriptnum_abs (const Bitcoin::integer &x, const Bitcoin::integer &y);

    uint256 secret_negate (const uint256 &x);
    uint256 secret_plus (const uint256 &x, const uint256 &y);
    uint256 secret_minus (const uint256 &x, const uint256 &y);
    uint256 secret_times (const uint256 &x, const uint256 &y);

    // base 58
    uint256 decode_base_58 (const data::string &x);
    data::string encode_base_58 (const uint256 &x);

    // advanced math
    uint256 secret_invert (const uint256 &x);
    uint256 secret_divide (const uint256 &x, const uint256 &y);

    uint256 secret_power (const uint256 &x, const uint256 &y);
    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const uint256 &y);

    // elliptic curve
    Bitcoin::integer secret_valid (const uint256 &x);
    Bitcoin::integer pubkey_valid (const secp256k1::pubkey &x);

    secp256k1::pubkey secret_to_public (const uint256 &x, const Bitcoin::integer &);

    Bitcoin::integer pubkey_compressed (const secp256k1::pubkey &x);
    Bitcoin::integer pubkey_uncompressed (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_compress (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_decompress (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const uint256 &y);
    secp256k1::pubkey pubkey_times (const uint256 &x, const secp256k1::pubkey &y);

    // script
    Bitcoin::integer push (const uint256 &x);
    Bitcoin::integer push (const Bitcoin::integer &x);
    Bitcoin::integer push (const data::string &x);
    Bitcoin::integer push (const secp256k1::pubkey &x);

    machine initialize () {

        machine m {};

        type nil {expression {}};

        m = m.define (symbol {"nil"}, nil, nil);

        // the fundamental types.
        type secret_type {symbol::make ("secret")};
        type pubkey_type {symbol::make ("pubkey")};
        type integer_type {symbol::make ("scriptnum")};
        type string_type {symbol::make ("string")};
        type sats_type {symbol::make ("satoshi")};
        type &bool_type = integer_type;

        expression X = symbol::make ("x");
        expression Y = symbol::make ("y");
        expression Z = symbol::make ("z");

        Symbol x = dynamic_cast<Symbol> (*X.get ());
        Symbol y = dynamic_cast<Symbol> (*Y.get ());
        Symbol z = dynamic_cast<Symbol> (*Y.get ());

        // bit operations
        m = m.define (unary_operand::tilda, integer_type, {integer_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_bit_not), {X}));
        m = m.define (symbol {"BitNot"}, integer_type, {{integer_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_bit_not), {X}));

        m = m.define (binary_operand::bit_and, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_and), {X, Y}));
        m = m.define (symbol {"BitAnd"}, integer_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_or, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_or), {X, Y}));
        m = m.define (symbol {"BitOr"}, integer_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_or), {X, Y}));

        m = m.define (binary_operand::bit_xor, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_xor), {X, Y}));
        m = m.define (symbol {"BitXor"}, integer_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_xor), {X, Y}));

        // boolean operations
        m = m.define (symbol {"False"}, bool_type, scriptnum::make (Bitcoin::integer {0}));
        m = m.define (symbol {"True"}, bool_type, scriptnum::make (Bitcoin::integer {1}));

        m = m.define (unary_operand::bool_not, bool_type, {bool_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_bool_not), {X}));

        m = m.define (symbol {"Not"}, bool_type, {{bool_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_bool_not), {X}));

        m = m.define (binary_operand::bool_and, bool_type, {bool_type, x}, {bool_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_and), {X, Y}));

        m = m.define (symbol {"And"}, bool_type, {{bool_type, x}, {bool_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_and), {X, Y}));

        m = m.define (binary_operand::bool_or, bool_type, {bool_type, x}, {bool_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_or), {X, Y}));

        m = m.define (symbol {"Or"}, bool_type, {{bool_type, x}, {bool_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_or), {X, Y}));

        // identical
        m = m.define (binary_operand::identical, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_identical), {X, Y}));

        m = m.define (symbol {"Identical"}, bool_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_identical), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const data::string &, const data::string &>::make (&string_equal), {X, Y}));

        m = m.define (symbol {"Identical"}, bool_type, {{string_type, x}, {string_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const data::string &, const data::string &>::make (&string_equal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_equal), {X, Y}));

        m = m.define (symbol {"Identical"}, bool_type, {{secret_type, x}, {secret_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_equal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_identical), {X, Y}));

        m = m.define (symbol {"Identical"}, bool_type, {{pubkey_type, x}, {pubkey_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_identical), {X, Y}));

        m = m.define (binary_operand::equal, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const data::string &, const data::string &>::make (string_equal), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const data::string &, const data::string &>::make (&string_unequal), {X, Y}));

        // comparisons
        m = m.define (binary_operand::equal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_equal), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_unequal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_less), {X, Y}));

        // comparisons
        m = m.define (binary_operand::equal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_equal), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_unequal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_less), {X, Y}));

        // arithmetic
        m = m.define (unary_operand::negate, integer_type, {integer_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_negate), {X}));

        m = m.define (binary_operand::plus, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_plus), {X, Y}));

        m = m.define (binary_operand::minus, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_minus), {X, Y}));

        m = m.define (binary_operand::times, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_times), {X, Y}));

        m = m.define (binary_operand::divide, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_divide), {X, Y}));

        m = m.define (binary_operand::mod, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_mod), {X, Y}));

        // arithmetic
        m = m.define (unary_operand::negate, secret_type, {secret_type, x},
            call::make (built_in_function<uint256,
                const uint256 &>::make (&secret_negate), {X}));

        m = m.define (binary_operand::plus, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<uint256,
                const uint256 &, const uint256 &>::make (&secret_plus), {X, Y}));

        m = m.define (binary_operand::minus, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<uint256,
                const uint256 &, const uint256 &>::make (&secret_minus), {X, Y}));

        m = m.define (binary_operand::times, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<uint256,
                const uint256 &, const uint256 &>::make (&secret_times), {X, Y}));

        m = m.define (symbol {"Invert"}, secret_type, {secret_type, x},
            call::make (built_in_function<uint256,
                const uint256 &>::make (&secret_invert), {X}));

        m = m.define (binary_operand::divide, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<uint256,
                const uint256 &, const uint256 &>::make (&secret_divide), {X}));

        // power
        m = m.define (binary_operand::power, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<uint256,
                const uint256 &, const uint256 &>::make (&secret_power), {X, Y}));

        m = m.define (symbol {"Power"}, secret_type, {{secret_type, x}, {secret_type, y}},
            call::make (built_in_function<uint256,
                const uint256 &, const uint256 &>::make (&secret_power), {X, Y}));

        m = m.define (binary_operand::power, integer_type, integer_type, integer_type,
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_power), {X, Y}));

        m = m.define (symbol {"Power"}, integer_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_power), {X, Y}));

        m = m.define (binary_operand::power, integer_type, integer_type, secret_type,
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_power), {X, Y}));

        m = m.define (symbol {"Power"}, integer_type, {{integer_type, x}, {secret_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_power), {X, Y}));

        // size operations
        m = m.define (symbol {"Size"}, integer_type, {{integer_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_size), {X}));
        m = m.define (symbol {"MinimalSize"}, integer_type, {{integer_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_minimal_size), {X}));
        m = m.define (symbol {"Minimal"}, integer_type, {{integer_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_minimal), {X}));
        m = m.define (symbol {"MinimalQ"}, bool_type, {{integer_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_is_minimal), {X}));
        m = m.define (symbol {"Resize"}, integer_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_negate), {X, Y}));
        m = m.define (symbol {"Resize"}, integer_type, {{integer_type, x}, {secret_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_negate), {X, Y}));

        // string operations
        m = m.define (binary_operand::cat, integer_type, {integer_type, x}, {integer_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_cat), {X, Y}));

        m = m.define (binary_operand::cat, string_type, {string_type, x}, {string_type, y},
            call::make (built_in_function<data::string,
                const data::string &, const data::string &>::make (&string_cat), {X, Y}));

        m = m.define (symbol {"Left"}, integer_type, {{integer_type, x}, {integer_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_left), {X, Y}));

        m = m.define (symbol {"Left"}, integer_type, {{integer_type, x}, {secret_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_left), {X, Y}));

        m = m.define (symbol {"Left"}, string_type, {{string_type, x}, {integer_type, y}},
            call::make (built_in_function<data::string,
                const data::string &, const Bitcoin::integer &>::make (&string_left), {X, Y}));

        m = m.define (symbol {"Left"}, string_type, {{string_type, x}, {secret_type, y}},
            call::make (built_in_function<data::string,
                const data::string &, const uint256 &>::make (&string_left), {X, Y}));

        m = m.define (symbol {"Right"}, integer_type, {{integer_type, x}, {integer_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_right), {X, Y}));

        m = m.define (symbol {"Right"}, integer_type, {{integer_type, x}, {secret_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_right), {X, Y}));

        m = m.define (symbol {"Right"}, string_type, {{string_type, x}, {integer_type, y}},
            call::make (built_in_function<data::string,
                const data::string &, const Bitcoin::integer &>::make (&string_right), {X, Y}));

        m = m.define (symbol {"Right"}, string_type, {{string_type, x}, {secret_type, y}},
            call::make (built_in_function<data::string,
                const data::string &, const uint256 &>::make (&string_right), {X, Y}));

        // bit shifts
        m = m.define (symbol {"RightShift"}, integer_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_right_shift), {X, Y}));

        m = m.define (symbol {"LeftShift"}, integer_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_left_shift), {X, Y}));

        m = m.define (symbol {"RightShift"}, integer_type, {{integer_type, x}, {secret_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_right_shift), {X, Y}));

        m = m.define (symbol {"LeftShift"}, integer_type, {{integer_type, x}, {secret_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_left_shift), {X, Y}));

        // push
        m = m.define (symbol {"Push"}, integer_type, {integer_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&push), {X}));

        m = m.define (symbol {"Push"}, integer_type, {string_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const data::string &>::make (&push), {X}));

        m = m.define (symbol {"Push"}, integer_type, {secret_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &>::make (&push), {X}));

        m = m.define (symbol {"Push"}, integer_type, {pubkey_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &>::make (&push), {X}));

        // base 58
        m = m.define (symbol {"Base58Decode"}, secret_type, {{string_type, x}},
            call::make (built_in_function<uint256,
                const data::string &>::make (&decode_base_58), {X}));

        m = m.define (symbol {"Base58Encode"}, string_type, {{secret_type, x}},
            call::make (built_in_function<data::string,
                const uint256 &>::make (&encode_base_58), {X}));

        // elliptic curve operations
        m = m.define (binary_operand::equal, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_equal), {X, Y}));

        m = m.define (binary_operand::equal, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_identical), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_unequal), {X, Y}));

        m = m.define (symbol {"Valid"}, integer_type, {{secret_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &>::make (&secret_valid), {X}));

        m = m.define (symbol {"Valid"}, integer_type, {{pubkey_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &>::make (&pubkey_valid), {X}));

        m = m.define (symbol {"ToPublic"}, pubkey_type, {{secret_type, x}, {bool_type, y}},
            call::make (built_in_function<secp256k1::pubkey,
                const uint256 &, const Bitcoin::integer &>::make (&secret_to_public), {X, Y}));

        m = m.define (symbol {"Compress"}, pubkey_type, {{pubkey_type, x}},
            call::make (built_in_function<secp256k1::pubkey,
                const secp256k1::pubkey &>::make (&pubkey_compress), {X}));

        m = m.define (symbol {"Deompress"}, pubkey_type, {{pubkey_type, x}},
            call::make (built_in_function<secp256k1::pubkey,
                const secp256k1::pubkey &>::make (&pubkey_decompress), {X}));

        m = m.define (symbol {"Compressed"}, bool_type, {{pubkey_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &>::make (&pubkey_compressed), {X}));

        m = m.define (symbol {"Unceompressed"}, bool_type, {{pubkey_type, x}},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &>::make (&pubkey_compressed), {X}));

        m = m.define (unary_operand::negate, pubkey_type, {pubkey_type, x},
            call::make (built_in_function<secp256k1::pubkey,
                const secp256k1::pubkey &>::make (&pubkey_negate), {X}));

        m = m.define (binary_operand::plus, pubkey_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_function<secp256k1::pubkey,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_plus), {X, Y}));

        m = m.define (binary_operand::times, pubkey_type, {secret_type, x}, {pubkey_type, y},
            call::make (built_in_function<secp256k1::pubkey,
                const uint256 &, const secp256k1::pubkey &>::make (&pubkey_times), {X, Y}));

        m = m.define (binary_operand::times, pubkey_type, {pubkey_type, x}, {secret_type, y},
            call::make (built_in_function<secp256k1::pubkey,
                const secp256k1::pubkey &, const uint256 &>::make (&pubkey_times), {X, Y}));

        // crypto
        m = m.declare (symbol {"Sign"}, integer_type, {secret_type, integer_type});

        m = m.declare (symbol {"Sign"}, integer_type, {secret_type, secret_type});

        m = m.declare (symbol {"Verify"}, bool_type, {pubkey_type, integer_type, integer_type});

        m = m.declare (symbol {"Verify"}, bool_type, {pubkey_type, secret_type, integer_type});

        // hash operations
        m = m.declare (symbol {"SHA"}, integer_type, {{secret_type, x}, {secret_type, y}, {integer_type, z}});
        m = m.declare (symbol {"RIPEMD"}, integer_type, {{secret_type, x}, {integer_type, y}});
        m = m.declare (symbol {"Hash160"}, integer_type, {{integer_type, x}});
        m = m.declare (symbol {"Hash256"}, integer_type, {{integer_type, x}});

        // make a random key using the given string as extra entropy.
        m = m.declare (symbol {"RandomKey"}, secret_type, {{integer_type, x}});
        m = m.declare (symbol {"RandomKey"}, secret_type, {{string_type, x}});

        return m;
    }

    Bitcoin::integer scriptnum_bool_not (const Bitcoin::integer &x) {
        return !x;
    }

    Bitcoin::integer scriptnum_bool_and (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x && y;
    }

    Bitcoin::integer scriptnum_bool_or (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x || y;
    }

    Bitcoin::integer scriptnum_bit_not (const Bitcoin::integer &x) {
        Bitcoin::integer z;
        z.resize (x.size ());
        for (int i = 0; i < z.size (); i++) z[i] = ~x[i];
        return z;
    }

    Bitcoin::integer scriptnum_bit_and (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        if (x.size () != y.size ()) throw data::exception {"BitAnd called on strings of different sizes"};
        Bitcoin::integer z;
        z.resize (x.size ());
        for (int i = 0; i < z.size (); i++) z[i] = x[i] & y[i];
        return z;
    }

    Bitcoin::integer scriptnum_bit_xor (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        if (x.size () != y.size ()) throw data::exception {"BitAnd called on strings of different sizes"};
        Bitcoin::integer z;
        z.resize (x.size ());
        for (int i = 0; i < z.size (); i++) z[i] = x[i] ^ y[i];
        return z;
    }

    Bitcoin::integer scriptnum_bit_or (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        if (x.size () != y.size ()) throw data::exception {"BitAnd called on strings of different sizes"};
        Bitcoin::integer z;
        z.resize (x.size ());
        for (int i = 0; i < z.size (); i++) z[i] = x[i] | y[i];
        return z;
    }

    Bitcoin::integer scriptnum_identical (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {data::identical (x, y)};
    }

    Bitcoin::integer string_equal (const data::string &x, const data::string &y) {
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer string_unequal (const data::string &x, const data::string &y) {
        return Bitcoin::integer {x != y};
    }

    Bitcoin::integer scriptnum_equal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x == y;
    }

    Bitcoin::integer scriptnum_unequal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x != y;
    }

    Bitcoin::integer scriptnum_greater_equal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x >= y;
    }

    Bitcoin::integer scriptnum_less_equal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x <= y;
    }

    Bitcoin::integer scriptnum_greater (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x > y;
    }

    Bitcoin::integer scriptnum_less (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x < y;
    }

    Bitcoin::integer scriptnum_negate (const Bitcoin::integer &x) {
        return -x;
    }

    Bitcoin::integer scriptnum_plus (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        std::cout << "calling scriptnum plus on " << x << " and " << y << std::endl;
        return x + y;
    }

    Bitcoin::integer scriptnum_minus (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x - y;
    }

    Bitcoin::integer scriptnum_times (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x * y;
    }

    Bitcoin::integer scriptnum_divide (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x / y;
    }

    Bitcoin::integer scriptnum_mod (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x % y;
    }

    Bitcoin::integer secret_identical (const uint256 &x, const uint256 &y) {
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer secret_equal (const uint256 &x, const uint256 &y) {
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer secret_unequal (const uint256 &x, const uint256 &y) {
        return Bitcoin::integer {x != y};
    }

    Bitcoin::integer secret_greater_equal (const uint256 &x, const uint256 &y) {
        return Bitcoin::integer {x <= y};
    }

    Bitcoin::integer secret_less_equal (const uint256 &x, const uint256 &y) {
        return Bitcoin::integer {x >= y};
    }

    Bitcoin::integer secret_greater (const uint256 &x, const uint256 &y) {
        return Bitcoin::integer {x < y};
    }

    Bitcoin::integer secret_less (const uint256 &x, const uint256 &y) {
        return Bitcoin::integer {x > y};
    }

    uint256 secp256k1_prime {"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f"};
    uint256 secp256k1_order {"0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141"};

    uint256 secret_negate (const uint256 &x) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        return x == 0 ? 0 : secp256k1_order - x;
    }

    uint256 secret_plus (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return static_cast<uint256> ((uint512 (x) + uint512 (y)) % uint512 (secp256k1_order));
    }

    uint256 secret_minus (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        auto order = uint512 (secp256k1_order);
        return static_cast<uint256> ((uint512 (x) + (order - uint512 (y))) % order);
    }

    uint256 secret_times (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return static_cast<uint256> ((uint512 (x) * uint512 (y)) % uint512 (secp256k1_order));
    }

    Bitcoin::integer scriptnum_size (const Bitcoin::integer &x) {
        return Bitcoin::integer {x.size ()};
    }

    Bitcoin::integer scriptnum_is_minimal (const Bitcoin::integer &x) {
        return Bitcoin::integer {is_minimal (x)};
    }

    Bitcoin::integer scriptnum_minimal_size (const Bitcoin::integer &x) {
        return Bitcoin::integer {minimal_size (x)};
    }

    Bitcoin::integer scriptnum_minimal (const Bitcoin::integer &x) {
        return Bitcoin::integer {trim (x)};
    }

    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {extend (x, static_cast<size_t> (data::int64 (y)))};
    }

    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::integer {extend (x, size_t (y))};
    }

    data::string string_cat (const data::string &x, const data::string &y) {
        return Bitcoin::cat (x, y);
    }

    data::string string_left (const data::string &x, const Bitcoin::integer &y) {
        return data::string {Bitcoin::left (x, static_cast<size_t> (data::int64 (y)))};
    }

    data::string string_left (const data::string &x, const uint256 &y) {
        return data::string {Bitcoin::left (x, size_t (y))};
    }

    data::string string_right (const data::string &x, const Bitcoin::integer &y) {
        return data::string {Bitcoin::right (x, static_cast<size_t> (data::int64 (y)))};
    }

    data::string string_right (const data::string &x, const uint256 &y) {
        return data::string {Bitcoin::right (x, size_t (y))};
    }

    Bitcoin::integer scriptnum_cat (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::cat (x, y);
    }

    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {Bitcoin::left (x, static_cast<size_t> (data::int64 (y)))};
    }

    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::integer {Bitcoin::left (x, size_t (y))};
    }

    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {Bitcoin::right (x, static_cast<size_t> (data::int64 (y)))};
    }

    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::integer {Bitcoin::right (x, size_t (y))};
    }

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::left_shift (x, static_cast<size_t> (data::int64 (y)));
    }

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::left_shift (x, size_t (y));
    }

    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::right_shift (x, static_cast<size_t> (data::int64 (y)));
    }

    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::right_shift (x, size_t (y));
    }

    Bitcoin::integer pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return x == y;
    }

    Bitcoin::integer pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return x != y;
    }

    Bitcoin::integer pubkey_unequal (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return static_cast<const data::bytes &> (x) == static_cast<const data::bytes &> (y);
    }

    uint256 decode_base_58 (const data::string &x) {
        data::maybe<uint256> result = data::encoding::base58::decode<uint256> (x);
        if (!bool (result)) throw data::exception {} << "invalid base 58 string";
        return *result;
    }

    data::string encode_base_58 (const uint256 &x) {
        std::cout << "encoding base 58: " << x << std::endl;
        return data::encoding::base58::encode<uint256> (x);
    }

    Bitcoin::integer secret_valid (const uint256 &x) {
        return Bitcoin::integer {x > 0 && x < secp256k1_order};
    }

    Bitcoin::integer pubkey_valid (const secp256k1::pubkey &x) {
        return Bitcoin::integer {x.valid ()};
    }

    secp256k1::pubkey secret_to_public (const uint256 &x, const Bitcoin::integer &y) {
        secp256k1::secret z {x};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";

        return z.to_public (bool (y));
    }

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return -x;
    }

    Bitcoin::integer pubkey_compressed (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return Bitcoin::integer {x.compressed ()};
    }

    Bitcoin::integer pubkey_uncompressed (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return Bitcoin::integer {!x.compressed ()};
    }

    secp256k1::pubkey pubkey_compress (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return x.compress ();
    }

    secp256k1::pubkey pubkey_decompress (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return x.decompress ();
    }

    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        if (!y.valid ()) throw data::exception {} << "invalid public key";
        return x + y;
    }

    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const uint256 &y) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        secp256k1::secret z {y};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";
        return x * z;
    }

    secp256k1::pubkey pubkey_times (const uint256 &x, const secp256k1::pubkey &y) {
        if (!y.valid ()) throw data::exception {} << "invalid public key";
        secp256k1::secret z {x};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";
        return y * z;
    }

    uint256 secret_invert (const uint256 &x) {
        if (!secret_valid (x)) throw data::exception {} << "invalid secret key";

        data::Z_bytes_little big_order (secp256k1_order);

        data::Z_bytes_little bt =
            data::math::number::euclidian::extended<data::N_bytes_little, data::Z_bytes_little>::algorithm
                (big_order, data::Z_bytes_little (x)).BezoutT;

        if (bt < 0) bt += big_order;

        return static_cast<uint256> (data::abs (bt));
    }

    uint256 secret_divide (const uint256 &x, const uint256 &y) {
        return secret_times (x, secret_invert (y));
    }

    uint256 secret_power (const uint256 &x, const uint256 &y) {
        return data::pow_mod (x, y, secp256k1_order);
    }

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const uint256 &y) {
        return data::pow (x, y);
    }

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return data::pow (x, y);
    }

    Bitcoin::integer push (const uint256 &x) {
        return Bitcoin::integer {Bitcoin::compile (Bitcoin::push_data (data::Z (data::Z_bytes_little (x))))};
    }

    Bitcoin::integer push (const Bitcoin::integer &x) {
        return Bitcoin::integer {Bitcoin::compile (Bitcoin::push_data (x))};
    }

    Bitcoin::integer push (const data::string &x) {
        return Bitcoin::integer {Bitcoin::compile (Bitcoin::push_data (data::bytes (x)))};
    }

    Bitcoin::integer push (const secp256k1::pubkey &x) {
        return Bitcoin::integer {Bitcoin::compile (Bitcoin::push_data (data::bytes (x)))};
    }

}

