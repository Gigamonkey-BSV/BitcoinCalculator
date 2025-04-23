#include <machine.hpp>
#include <values/leaf.hpp>
#include <values/list.hpp>
#include <built.in/bool.hpp>
#include <built.in/hash.hpp>
#include <built.in/base58.hpp>

namespace Diophant {

    // script
    Bitcoin::integer push (const uint256 &x);
    Bitcoin::integer push (const Bitcoin::integer &x);
    Bitcoin::integer push (const data::string &x);
    Bitcoin::integer push (const secp256k1::pubkey &x);

    // crypto
    Bitcoin::integer sign (const uint256 &key, const uint256 &digest);
    bool verify (const secp256k1::pubkey &x, const uint256 &digest, const Bitcoin::integer &sig);

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

        m = m.define (symbol {"nil"}, nil, nil);

        type bool_type {symbol::make ("boolean")};

        m = m.define (symbol {"false"}, bool_type, boolean::make (false));
        m = m.define (symbol {"true"}, bool_type, boolean::make (true));

        m = m.define (unary_operand::bool_not, bool_type, {bool_type, x},
            call::make (built_in_func<bool, bool>::make (&bool_not), {X}));

        m = m.define (symbol {"not"}, bool_type, {{bool_type, x}},
            call::make (built_in_func<bool, bool>::make (&bool_not), {X}));

        m = m.define (binary_operand::bool_and, bool_type, {bool_type, x}, {bool_type, y},
            call::make (built_in_func<bool, bool, bool>::make (&bool_and), {X, Y}));

        m = m.define (symbol {"and"}, bool_type, {{bool_type, x}, {bool_type, y}},
            call::make (built_in_func<bool, bool, bool>::make (&bool_and), {X, Y}));

        m = m.define (binary_operand::bool_or, bool_type, {bool_type, x}, {bool_type, y},
            call::make (built_in_func<bool, bool, bool>::make (&bool_or), {X, Y}));

        m = m.define (symbol {"or"}, bool_type, {{bool_type, x}, {bool_type, y}},
            call::make (built_in_func<bool, bool, bool>::make (&bool_or), {X, Y}));

        m = m.define (symbol {"implies"}, bool_type, {{bool_type, x}, {bool_type, y}},
            call::make (built_in_func<bool, bool, bool>::make (&bool_implies), {X, Y}));

        m = m.define (symbol {"xor"}, bool_type, {{bool_type, x}, {bool_type, y}},
            call::make (built_in_func<bool, bool, bool>::make (&bool_xor), {X, Y}));

        m = m.define (symbol {"nand"}, bool_type, {{bool_type, x}, {bool_type, y}},
            call::make (built_in_func<bool, bool, bool>::make (&bool_nand), {X, Y}));

        m = m.define (symbol {"nor"}, bool_type, {{bool_type, x}, {bool_type, y}},
            call::make (built_in_func<bool, bool, bool>::make (&bool_nor), {X, Y}));

        // next we have some basic number types.
        type int8_type {call::make (symbol::make ("int"), {natural::make (data::N (8))})};
        type uint8_type {call::make (symbol::make ("uint"), {natural::make (data::N (8))})};

        m = m.define (symbol {"byte"}, uint8_type);
        m = m.define (symbol {"char"}, int8_type);

        type int16_type {call::make (symbol::make ("int"), {natural::make (data::N (16))})};
        type uint16_type {call::make (symbol::make ("uint"), {natural::make (data::N (16))})};

        type int16_little_type {call::make (symbol::make ("int"), {natural::make (data::N (16))})};
        type uint16_little_type {call::make (symbol::make ("uint"), {natural::make (data::N (16))})};

        type int16_big_type {call::make (symbol::make ("int"), {natural::make (data::N (16))})};
        type uint16_big_type {call::make (symbol::make ("uint"), {natural::make (data::N (16))})};

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

        type int128_type {call::make (symbol::make ("int"), {natural::make (data::N (128))})};
        type uint128_type {call::make (symbol::make ("uint"), {natural::make (data::N (128))})};

        type int128_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (128))})};
        type uint128_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (128))})};

        type int128_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (128))})};
        type uint128_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (128))})};

        type int160_type {call::make (symbol::make ("int"), {natural::make (data::N (160))})};
        type uint160_type {call::make (symbol::make ("uint"), {natural::make (data::N (160))})};

        type int160_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (160))})};
        type uint160_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (160))})};

        type int160_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (160))})};
        type uint160_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (160))})};

        type int256_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (256))})};
        type uint256_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (256))})};

        type int256_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (256))})};
        type uint256_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (256))})};

        type int256_type {call::make (symbol::make ("int"), {natural::make (data::N (256))})};
        type uint256_type {call::make (symbol::make ("uint"), {natural::make (data::N (256))})};

        type int512_little_type {call::make (symbol::make ("int_little"), {natural::make (data::N (512))})};
        type uint512_little_type {call::make (symbol::make ("uint_little"), {natural::make (data::N (512))})};

        type int512_big_type {call::make (symbol::make ("int_big"), {natural::make (data::N (512))})};
        type uint512_big_type {call::make (symbol::make ("uint_big"), {natural::make (data::N (512))})};

        type int512_type {call::make (symbol::make ("int"), {natural::make (data::N (512))})};
        type uint512_type {call::make (symbol::make ("uint"), {natural::make (data::N (512))})};

        type integer_type {symbol::make ("integer")};

        type bytes_type {symbol::make ("bytes")};
        type string_type {symbol::make ("string")};
        type scriptnum_type {symbol::make ("scriptnum")};
        type coord_type {symbol::make ("coordinate")};
        type secret_type {symbol::make ("secret")};
        type pubkey_type {symbol::make ("pubkey")};
        type sats_type {symbol::make ("satoshi")};

        m = m.define (symbol {"address_main"}, byte::make (data::byte (0x00)));
        m = m.define (symbol {"address_test"}, byte::make (data::byte (0x6f)));
        m = m.define (symbol {"WIF_main"}, byte::make (data::byte (0x80)));
        m = m.define (symbol {"WIF_test"}, byte::make (data::byte (0xef)));
        m = m.define (symbol {"sighash_all"}, byte::make (data::byte (1)));
        m = m.define (symbol {"sighash_none"}, byte::make (data::byte (2)));
        m = m.define (symbol {"sighash_single"}, byte::make (data::byte (3)));
        m = m.define (symbol {"sighash_anyone_can_pay"}, byte::make (data::byte (0x80)));
        m = m.define (symbol {"sighash_forkid"}, byte::make (data::byte (0x40)));

        m = m.define (symbol {"Satoshi"}, call::make (symbol::make ("sats"), {int64_little_type}));
        m = m.define (symbol {"Coordinate"}, call::make (symbol::make ("coord"), {uint256_little_type}));
        m = m.define (symbol {"Secret"}, call::make (symbol::make ("secret"), {uint256_little_type}));
        m = m.define (symbol {"Pubkey"}, call::make (symbol::make ("pubkey"), {bytes_type}));
        m = m.define (symbol {"ScriptNum"}, call::make (symbol::make ("scriptnum"), {bytes_type}));

        // scriptnum bit operations
        m = m.define (unary_operand::tilda, scriptnum_type, {scriptnum_type, x},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_bit_not), {X}));
        m = m.define (symbol {"bit_not"}, scriptnum_type, {{scriptnum_type, x}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_bit_not), {X}));

        m = m.define (binary_operand::bit_and, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_and), {X, Y}));
        m = m.define (symbol {"bit_and"}, scriptnum_type, {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_or, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_or), {X, Y}));
        m = m.define (symbol {"bit_or"}, scriptnum_type, {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_or), {X, Y}));

        m = m.define (binary_operand::bit_xor, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_xor), {X, Y}));
        m = m.define (symbol {"bit_xor"}, scriptnum_type, {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_xor), {X, Y}));

        // scriptnum boolean operations
        m = m.define (unary_operand::bool_not, scriptnum_type, {scriptnum_type, x},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_bool_not), {X}));

        m = m.define (symbol {"not"}, scriptnum_type, {{scriptnum_type, x}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_bool_not), {X}));

        m = m.define (binary_operand::bool_and, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_and), {X, Y}));

        m = m.define (symbol {"and"}, scriptnum_type, {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_and), {X, Y}));

        m = m.define (binary_operand::bool_or, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_or), {X, Y}));

        m = m.define (symbol {"or"}, scriptnum_type, {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_or), {X, Y}));

        // identical
        m = m.define (binary_operand::identical, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_identical), {X, Y}));

        m = m.define (symbol {"identical"}, scriptnum_type, {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_identical), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_func<bool,
                const data::string &, const data::string &>::make (&string_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{string_type, x}, {string_type, y}},
            call::make (built_in_func<bool,
                const data::string &, const data::string &>::make (&string_equal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&secret_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{secret_type, x}, {secret_type, y}},
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&secret_equal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_identical), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{pubkey_type, x}, {pubkey_type, y}},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_identical), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_func<bool,
                const data::string &, const data::string &>::make (string_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_func<bool,
                const data::string &, const data::string &>::make (&string_unequal), {X, Y}));

        // comparisons
        m = m.define (binary_operand::bool_equal, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_unequal), {X, Y}));

        m = m.define (binary_operand::greater_equal, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_greater), {X, Y}));

        m = m.define (binary_operand::less, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_less), {X, Y}));

        // comparisons for secret keys
        m = m.define (binary_operand::bool_equal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&secret_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&secret_unequal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&secret_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&secret_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&secret_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&secret_less), {X, Y}));

        // comparisons for coordinates
        m = m.define (binary_operand::bool_equal, bool_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&coord_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&coord_unequal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&coord_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&coord_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&coord_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (built_in_func<bool,
                const uint256 &, const uint256 &>::make (&coord_less), {X, Y}));

        // arithmetic
        m = m.define (unary_operand::negate, scriptnum_type, {scriptnum_type, x},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_negate), {X}));

        m = m.define (binary_operand::plus, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_plus), {X, Y}));

        m = m.define (binary_operand::minus, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_minus), {X, Y}));

        m = m.define (binary_operand::times, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_times), {X, Y}));

        m = m.define (binary_operand::divide, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_divide), {X, Y}));

        m = m.define (binary_operand::mod, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_mod), {X, Y}));

        // arithmetic
        m = m.define (unary_operand::negate, secret_type, {secret_type, x},
            call::make (built_in_func<uint256,
                const uint256 &>::make (&secret_negate), {X}));

        m = m.define (binary_operand::plus, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&secret_plus), {X, Y}));

        m = m.define (binary_operand::minus, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&secret_minus), {X, Y}));

        m = m.define (binary_operand::times, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&secret_times), {X, Y}));

        m = m.define (symbol {"invert"}, secret_type, {{secret_type, x}},
            call::make (built_in_func<uint256,
                const uint256 &>::make (&secret_invert), {X}));

        m = m.define (binary_operand::divide, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&secret_divide), {X, Y}));

        // arithmetic for coordinates
        m = m.define (unary_operand::negate, coord_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<uint256,
                const uint256 &>::make (&coord_negate), {X})}));

        m = m.define (binary_operand::plus, coord_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&coord_plus), {X, Y})}));

        m = m.define (binary_operand::minus, coord_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&coord_minus), {X, Y})}));

        m = m.define (binary_operand::times, coord_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&coord_times), {X, Y})}));

        m = m.define (symbol {"invert"}, coord_type,
            {call::make (symbol::make ("coord"), {pattern {secret_type, x}})},
            call::make (symbol::make ("coord"), {call::make (built_in_func<uint256,
                const uint256 &>::make (&coord_invert), {X})}));

        m = m.define (binary_operand::divide, coord_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&coord_divide), {X, Y})}));

        // power
        m = m.define (binary_operand::power, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&secret_power), {X, Y}));

        m = m.define (symbol {"power"}, secret_type, {{secret_type, x}, {secret_type, y}},
            call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&secret_power), {X, Y}));

        m = m.define (binary_operand::power, scriptnum_type, {scriptnum_type, x}, {scriptnum_type, x},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_power), {X, Y}));

        m = m.define (symbol {"power"}, scriptnum_type, {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_power), {X, Y}));

        m = m.define (binary_operand::power, scriptnum_type,
            call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
            call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&coord_power), {X, Y})}));

        m = m.define (symbol {"power"}, scriptnum_type, {
                call::make (symbol::make ("coord"), {pattern {secret_type, x}}),
                call::make (symbol::make ("coord"), {pattern {secret_type, y}}),
            }, call::make (symbol::make ("coord"), {call::make (built_in_func<uint256,
                const uint256 &, const uint256 &>::make (&coord_divide), {X, Y})}));

        // size operations
        m = m.define (symbol {"size"}, scriptnum_type, {{scriptnum_type, x}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_size), {X}));
        m = m.define (symbol {"minimal_size"}, scriptnum_type, {{scriptnum_type, x}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_minimal_size), {X}));
        m = m.define (symbol {"minimal"}, scriptnum_type, {{scriptnum_type, x}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_minimal), {X}));
        m = m.define (symbol {"is_minimal"}, bool_type, {{scriptnum_type, x}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_is_minimal), {X}));
        m = m.define (symbol {"resize"}, scriptnum_type, {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_negate), {X, Y}));
        m = m.define (symbol {"resize"}, scriptnum_type, {{scriptnum_type, x}, {secret_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_negate), {X, Y}));

        // string operations
        m = m.define (binary_operand::cat, scriptnum_type,
            {scriptnum_type, x}, {scriptnum_type, y},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_cat), {X, Y}));

        m = m.define (binary_operand::cat, string_type,
            {string_type, x}, {string_type, y},
            call::make (built_in_func<data::string,
                const data::string &, const data::string &>::make (&string_cat), {X, Y}));

        m = m.define (symbol {"left"}, scriptnum_type,
            {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_left), {X, Y}));

        m = m.define (symbol {"left"}, scriptnum_type,
            {{scriptnum_type, x}, {secret_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_left), {X, Y}));

        m = m.define (symbol {"left"}, string_type,
            {{string_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const Bitcoin::integer &>::make (&string_left), {X, Y}));

        m = m.define (symbol {"left"}, string_type,
            {{string_type, x}, {secret_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const uint256 &>::make (&string_left), {X, Y}));

        m = m.define (symbol {"right"}, scriptnum_type,
            {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_right), {X, Y}));

        m = m.define (symbol {"right"}, scriptnum_type,
            {{scriptnum_type, x}, {secret_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_right), {X, Y}));

        m = m.define (symbol {"right"}, string_type,
            {{string_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const Bitcoin::integer &>::make (&string_right), {X, Y}));

        m = m.define (symbol {"right"}, string_type,
            {{string_type, x}, {secret_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const uint256 &>::make (&string_right), {X, Y}));

        m = m.define (symbol {"split"}, list::make ({scriptnum_type, scriptnum_type}),
            {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<std::tuple<Bitcoin::integer, Bitcoin::integer>,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_split), {X, Y}));

        m = m.define (symbol {"split"}, list::make ({scriptnum_type, scriptnum_type}),
            {{scriptnum_type, x}, {secret_type, y}},
            call::make (built_in_func<std::tuple<Bitcoin::integer, Bitcoin::integer>,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_split), {X, Y}));

        m = m.define (symbol {"split"}, list::make ({string_type, string_type}),
            {{string_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<std::tuple<data::string, data::string>,
                const data::string &, const Bitcoin::integer &>::make (&string_split), {X, Y}));

        m = m.define (symbol {"split"}, list::make ({string_type, string_type}),
            {{string_type, x}, {secret_type, y}},
            call::make (built_in_func<std::tuple<data::string, data::string>,
                const data::string &, const uint256 &>::make (&string_split), {X, Y}));

        // bit shifts
        m = m.define (symbol {"right_shift"}, scriptnum_type,
            {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_right_shift), {X, Y}));

        m = m.define (symbol {"left_shift"}, scriptnum_type,
            {{scriptnum_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_left_shift), {X, Y}));

        m = m.define (symbol {"right_shift"}, scriptnum_type,
            {{scriptnum_type, x}, {secret_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_right_shift), {X, Y}));

        m = m.define (symbol {"left_shift"}, scriptnum_type,
            {{scriptnum_type, x}, {secret_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &, const uint256 &>::make (&scriptnum_left_shift), {X, Y}));

        // push
        m = m.define (symbol {"push"}, scriptnum_type, {scriptnum_type, x},
            call::make (built_in_func<Bitcoin::integer,
                const Bitcoin::integer &>::make (&push), {X}));

        m = m.define (symbol {"push"}, scriptnum_type, {string_type, x},
            call::make (built_in_func<Bitcoin::integer,
                const data::string &>::make (&push), {X}));

        m = m.define (symbol {"push"}, scriptnum_type, {secret_type, x},
            call::make (built_in_func<Bitcoin::integer,
                const uint256 &>::make (&push), {X}));

        m = m.define (symbol {"push"}, scriptnum_type, {pubkey_type, x},
            call::make (built_in_func<Bitcoin::integer,
                const secp256k1::pubkey &>::make (&push), {X}));

        // base 58
        m = m.define (symbol {"base58_decode"}, secret_type, {{string_type, x}},
            call::make (built_in_func<uint256,
                const data::string &>::make (&decode_base_58), {X}));

        m = m.define (symbol {"base58_encode"}, string_type, {{secret_type, x}},
            call::make (built_in_func<data::string,
                const uint256 &>::make (&encode_base_58), {X}));

        m = m.define (symbol {"base58_check_decode"}, list::make ({uint8_type, scriptnum_type}),
            {pattern {string_type, x}},
            call::make (built_in_func<std::tuple<data::byte, Bitcoin::integer>,
                const data::string &>::make (&decode_base_58_check), {X}));

        m = m.define (symbol {"base58_check_encode"}, string_type,
            {list::make ({pattern {uint8_type, x}, pattern {scriptnum_type, y}})},
            call::make (built_in_func<data::string,
                const data::byte &, const Bitcoin::integer &>::make (&encode_base_58_check), {X, Y}));

        // elliptic curve operations
        m = m.define (binary_operand::bool_unequal, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_unequal), {X, Y}));

        m = m.define (symbol {"valid"}, scriptnum_type, {{secret_type, x}},
            call::make (built_in_func<bool,
                const uint256 &>::make (&secret_valid), {X}));

        m = m.define (symbol {"valid"}, scriptnum_type, {{pubkey_type, x}},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &>::make (&pubkey_valid), {X}));

        m = m.define (symbol {"to_public"}, pubkey_type, {{bool_type, x}, {secret_type, y}},
            call::make (built_in_func<secp256k1::pubkey,
                bool, const uint256 &>::make (&secret_to_public), {X, Y}));

        m = m.define (symbol {"compress"}, pubkey_type, {{pubkey_type, x}},
            call::make (built_in_func<secp256k1::pubkey,
                const secp256k1::pubkey &>::make (&pubkey_compress), {X}));

        m = m.define (symbol {"deompress"}, pubkey_type, {{pubkey_type, x}},
            call::make (built_in_func<secp256k1::pubkey,
                const secp256k1::pubkey &>::make (&pubkey_decompress), {X}));

        m = m.define (symbol {"compressed"}, bool_type, {{pubkey_type, x}},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &>::make (&pubkey_compressed), {X}));

        m = m.define (symbol {"uncompressed"}, bool_type, {{pubkey_type, x}},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &>::make (&pubkey_compressed), {X}));

        m = m.define (unary_operand::negate, pubkey_type, {pubkey_type, x},
            call::make (built_in_func<secp256k1::pubkey,
                const secp256k1::pubkey &>::make (&pubkey_negate), {X}));

        m = m.define (binary_operand::plus, pubkey_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_func<secp256k1::pubkey,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_plus), {X, Y}));

        m = m.define (binary_operand::times, pubkey_type, {secret_type, x}, {pubkey_type, y},
            call::make (built_in_func<secp256k1::pubkey,
                const uint256 &, const secp256k1::pubkey &>::make (&pubkey_times), {X, Y}));

        m = m.define (binary_operand::times, pubkey_type, {pubkey_type, x}, {secret_type, y},
            call::make (built_in_func<secp256k1::pubkey,
                const secp256k1::pubkey &, const uint256 &>::make (&pubkey_times), {X, Y}));

        // crypto
        m = m.define (symbol {"sign"}, scriptnum_type, {{secret_type, x}, {secret_type, y}},
            call::make (built_in_func<Bitcoin::integer,
                const uint256 &, const uint256 &>::make (&sign), {X, Y}));

        m = m.define (symbol {"verify"}, bool_type, {{pubkey_type, x}, {secret_type, y}, {scriptnum_type, z}},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const uint256 &, const Bitcoin::integer &>::make (&verify), {X, Y, Z}));

        m = m.define (symbol {"SHA2_256"}, secret_type, {{scriptnum_type, x}},
            call::make (built_in_func<uint256, const Bitcoin::integer &>::make (&SHA2_256), {X}));

        m = m.define (symbol {"SHA3_256"}, secret_type, {{scriptnum_type, x}},
            call::make (built_in_func<uint256, const Bitcoin::integer &>::make (&SHA3_256), {X}));

        m = m.define (symbol {"SHA2_256"}, secret_type, {{string_type, x}},
            call::make (built_in_func<uint256, const data::string &>::make (&SHA2_256), {X}));

        m = m.define (symbol {"SHA3_256"}, secret_type, {{string_type, x}},
            call::make (built_in_func<uint256, const data::string &>::make (&SHA3_256), {X}));

        m = m.define (symbol {"Hash256"}, secret_type, {{scriptnum_type, x}},
            call::make (built_in_func<uint256, const Bitcoin::integer &>::make (&Hash256), {X}));

        m = m.define (symbol {"Hash256"}, secret_type, {{string_type, x}},
            call::make (built_in_func<uint256, const data::string &>::make (&Hash256), {X}));

        m = m.define (symbol {"Hash160"}, scriptnum_type, {{scriptnum_type, x}},
            call::make (built_in_func<Bitcoin::integer, const Bitcoin::integer &>::make (&Hash160), {X}));

        m = m.define (symbol {"Hash160"}, scriptnum_type, {{string_type, x}},
            call::make (built_in_func<Bitcoin::integer, const data::string &>::make (&Hash160), {X}));

        m = m.define (symbol {"Hash160"}, scriptnum_type, {{pubkey_type, x}},
            call::make (built_in_func<Bitcoin::integer, const secp256k1::pubkey &>::make (&Hash160), {X}));

        return m;
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

    bool verify (const secp256k1::pubkey &x, const uint256 &digest, const Bitcoin::integer &sig) {
        return x.verify (digest, secp256k1::signature {sig});
    }

}

