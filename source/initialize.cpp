#include <machine.hpp>
#include <values/leaf.hpp>
#include <built.in/pubkey.hpp>

namespace Diophant {

    // bool operations
    bool bool_not (const bool &x);
    bool bool_and (const bool &x, const bool &y);
    bool bool_or (const bool &x, const bool &y);
    bool bool_implies (const bool &x, const bool &y);
    bool bool_xor (const bool &x, const bool &y);
    bool bool_nand (const bool &x, const bool &y);
    bool bool_nor (const bool &x, const bool &y);

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

    Bitcoin::integer string_equal (const data::string &x, const data::string &y);
    Bitcoin::integer string_unequal (const data::string &x, const data::string &y);

    // size operations
    data::string string_size (const data::string &x);

    // base 58
    uint256 decode_base_58 (const data::string &x);
    data::string encode_base_58 (const uint256 &x);


    // script
    Bitcoin::integer push (const uint256 &x);
    Bitcoin::integer push (const Bitcoin::integer &x);
    Bitcoin::integer push (const data::string &x);
    Bitcoin::integer push (const secp256k1::pubkey &x);

    // crypto
    Bitcoin::integer sign (const uint256 &key, const uint256 &digest);
    Bitcoin::integer verify (const secp256k1::pubkey &x, const uint256 &digest, const Bitcoin::integer &sig);

    uint256 SHA2_256 (const Bitcoin::integer &key);
    uint256 SHA2_256 (const data::string &key);
    uint256 SHA3_256 (const Bitcoin::integer &key);
    uint256 SHA3_256 (const data::string &key);
    uint256 Hash256 (const Bitcoin::integer &key);
    uint256 Hash256 (const data::string &key);

    machine initialize () {

        machine m {};

        expression X = symbol::make ("x");
        expression Y = symbol::make ("y");
        expression Z = symbol::make ("z");

        Symbol x = dynamic_cast<Symbol> (*X.get ());
        Symbol y = dynamic_cast<Symbol> (*Y.get ());
        Symbol z = dynamic_cast<Symbol> (*Z.get ());

        type undefined {expression {}};
        type nil {Diophant::nil::make ()};

        m = m.define (symbol {"Nil"}, nil, nil);

        //type bool_type {symbol::make ("bool")};

        // next we have some basic number types.
        type int8_type {call::make (symbol::make ("int"), {natural::make (data::N (8))})};
        type uint8_type {call::make (symbol::make ("uint"), {natural::make (data::N(8))})};

        m = m.define (symbol {"byte"}, uint8_type);
        m = m.define (symbol {"char"}, int8_type);

        type int16_type {call::make (symbol::make ("int"), {natural::make (data::N (16))})};
        type uint16_type {call::make (symbol::make ("uint"), {natural::make (data::N (16))})};

        type int32_type {call::make (symbol::make ("int"), {natural::make (data::N (32))})};
        type uint32_type {call::make (symbol::make ("uint"), {natural::make (data::N (32))})};

        type int32_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (32))})};
        type uint32_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (32))})};

        type int32_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (32))})};
        type uint32_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (32))})};

        type int64_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (64))})};
        type uint64_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (64))})};

        type int64_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (64))})};
        type uint64_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (64))})};

        type int64_type {call::make (symbol::make ("int"), {natural::make (data::N (64))})};
        type uint64_type {call::make (symbol::make ("uint"), {natural::make (data::N (64))})};

        type int128_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (128))})};
        type uint128_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (128))})};

        type int128_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (128))})};
        type uint128_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (128))})};

        type int128_type {call::make (symbol::make ("int"), {natural::make (data::N (128))})};
        type uint128_type {call::make (symbol::make ("uint"), {natural::make (data::N (128))})};

        m = m.define (symbol {"int"}, data::stack<pattern> {natural::make (data::N (128))}, int128_little_type);
        m = m.define (symbol {"uint"}, data::stack<pattern> {natural::make (data::N (128))}, uint128_little_type);

        type int160_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (160))})};
        type uint160_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (160))})};

        type int160_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (160))})};
        type uint160_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (160))})};

        type int160_type {call::make (symbol::make ("int"), {natural::make (data::N (160))})};
        type uint160_type {call::make (symbol::make ("uint"), {natural::make (data::N (160))})};

        m = m.define (symbol {"int"}, data::stack<pattern> {natural::make (data::N (160))}, int160_little_type);
        m = m.define (symbol {"uint"}, data::stack<pattern> {natural::make (data::N (160))}, uint160_little_type);

        type int256_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (256))})};
        type uint256_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (256))})};

        type int256_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (256))})};
        type uint256_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (256))})};

        type int256_type {call::make (symbol::make ("int"), {natural::make (data::N (256))})};
        type uint256_type {call::make (symbol::make ("uint"), {natural::make (data::N (256))})};

        m = m.define (symbol {"int"}, data::stack<pattern> {natural::make (data::N (256))}, int256_little_type);
        m = m.define (symbol {"uint"}, data::stack<pattern> {natural::make (data::N (256))}, uint256_little_type);

        type int512_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (512))})};
        type uint512_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (512))})};

        type int512_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (512))})};
        type uint512_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (512))})};

        type int512_type {call::make (symbol::make ("int"), {natural::make (data::N (512))})};
        type uint512_type {call::make (symbol::make ("uint"), {natural::make (data::N (512))})};

        m = m.define (symbol {"int"}, data::stack<pattern> {natural::make (data::N (512))}, int512_little_type);
        m = m.define (symbol {"uint"}, data::stack<pattern> {natural::make (data::N (512))}, uint512_little_type);

        type bytes_type {symbol::make ("bytes")};
        type string_type {symbol::make ("string")};
        type integer_type {symbol::make ("scriptnum")};
        type secret_type {symbol::make ("secret")};
        type pubkey_type {symbol::make ("pubkey")};
        type sats_type {symbol::make ("satoshi")};
        type &bool_type = integer_type;

        m = m.define (symbol {"satoshi"}, call::make (symbol::make ("Satoshi"), {int64_little_type}));
        m = m.define (symbol {"coordinate"}, call::make (symbol::make ("Coordinate"), {uint256_little_type}));
        m = m.define (symbol {"secret"}, call::make (symbol::make ("Secret"), {uint256_little_type}));
        m = m.define (symbol {"pubkey"}, call::make (symbol::make ("Pubkey"), {bytes_type}));
        m = m.define (symbol {"scriptnum"}, call::make (symbol::make ("ScriptNum"), {bytes_type}));

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

        // comparisons for secret keys
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
/*
        // comparisons for coordinates
        m = m.define (binary_operand::equal, bool_type, pattern {secret_type, x}, pattern {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_equal), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, pattern {secret_type, x}, pattern {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_unequal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, pattern {secret_type, x}, pattern {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, pattern {secret_type, x}, pattern {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, pattern {secret_type, x}, pattern {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, pattern {secret_type, x}, pattern {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&secret_less), {X, Y}));*/

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
        m = m.define (symbol {"Sign"}, integer_type, {{secret_type, x}, {secret_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&sign), {X, Y}));

        m = m.define (symbol {"Verify"}, bool_type, {{pubkey_type, x}, {secret_type, y}, {integer_type, z}},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::pubkey &, const uint256 &, const Bitcoin::integer &>::make (&verify), {X, Y, Z}));

        m = m.define (symbol {"SHA2_256"}, secret_type, {{integer_type, x}},
            call::make (built_in_function<uint256, const Bitcoin::integer &>::make (&SHA2_256), {X}));

        m = m.define (symbol {"SHA3_256"}, secret_type, {{integer_type, x}},
            call::make (built_in_function<uint256, const Bitcoin::integer &>::make (&SHA2_256), {X}));

        m = m.define (symbol {"Hash256"}, secret_type, {{integer_type, x}},
            call::make (built_in_function<uint256, const Bitcoin::integer &>::make (&SHA2_256), {X}));

        m = m.define (symbol {"SHA2_256"}, secret_type, {{string_type, x}},
            call::make (built_in_function<uint256, const data::string &>::make (&SHA2_256), {X}));

        m = m.define (symbol {"SHA3_256"}, secret_type, {{string_type, x}},
            call::make (built_in_function<uint256, const data::string &>::make (&SHA2_256), {X}));

        m = m.define (symbol {"Hash256"}, secret_type, {{string_type, x}},
            call::make (built_in_function<uint256, const data::string &>::make (&SHA2_256), {X}));

        return m;
    }

    Bitcoin::integer string_equal (const data::string &x, const data::string &y) {
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer string_unequal (const data::string &x, const data::string &y) {
        return Bitcoin::integer {x != y};
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

    uint256 decode_base_58 (const data::string &x) {
        data::maybe<uint256> result = data::encoding::base58::decode<uint256> (x);
        if (!bool (result)) throw data::exception {} << "invalid base 58 string";
        return *result;
    }

    data::string encode_base_58 (const uint256 &x) {
        return data::encoding::base58::encode<uint256> (x);
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

    Bitcoin::integer sign (const uint256 &key, const uint256 &digest) {
        return Bitcoin::integer {secp256k1::secret {key}.sign (digest)};
    }

    Bitcoin::integer verify (const secp256k1::pubkey &x, const uint256 &digest, const Bitcoin::integer &sig) {
        return Bitcoin::integer {x.verify (digest, secp256k1::signature {sig})};
    }

    uint256 SHA2_256 (const Bitcoin::integer &key) {
        return data::crypto::SHA2_256 (key);
    }

    uint256 SHA2_256 (const data::string &key) {
        return data::crypto::SHA2_256 (key);
    }

    uint256 SHA3_256 (const Bitcoin::integer &key) {
        return data::crypto::SHA3_256 (key);
    }

    uint256 SHA3_256 (const data::string &key) {
        return data::crypto::SHA3_256 (key);
    }

    uint256 Hash256 (const Bitcoin::integer &key) {
        return data::crypto::Bitcoin_256 (key);
    }

    uint256 Hash256 (const data::string &key) {
        return data::crypto::Bitcoin_256 (key);
    }

}

