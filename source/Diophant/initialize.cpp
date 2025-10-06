#include <Diophant/machine.hpp>
#include <Diophant/values/leaf.hpp>
#include <Diophant/values/list.hpp>
#include <Diophant/values/struct.hpp>
#include <Diophant/built.in/bool.hpp>
#include <Diophant/built.in/numbers.hpp>
#include <Diophant/built.in/hash.hpp>
#include <Diophant/built.in/base58.hpp>
#include <Diophant/built.in/hd.hpp>

namespace Diophant {

    // script
    data::bytes push (const data::uint256_little &x);
    data::bytes push (const Bitcoin::integer &x);
    data::bytes push (const data::bytes &x);
    data::bytes push (const secp256k1::pubkey &x);

    // crypto

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

        // we start with boolean functions.
        type bool_type {symbol::make ("bool")};

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

        // Here we have unbounded number types.
        type natural_type {symbol::make ("N")};
        type integer_type {symbol::make ("Z")};

        m = m.define (binary_operand::bool_equal, bool_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (natural_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (natural_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (natural_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{natural_type, x}, {natural_type, y}},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (natural_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<bool,
                const data::Z &, const data::Z &>::make (integer_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<bool,
                const data::Z &, const data::Z &>::make (integer_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<bool,
                const data::Z &, const data::Z &>::make (integer_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_func<bool,
                const data::Z &, const data::Z &>::make (integer_equal), {X, Y}));

        // comparisons for unbounded types
        m = m.define (binary_operand::greater_equal, bool_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (natural_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (natural_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (natural_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (natural_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<bool,
                const data::Z &, const data::Z &>::make (integer_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<bool,
                const data::Z &, const data::Z &>::make (integer_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<bool,
                const data::Z &, const data::Z &>::make (integer_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<bool,
                const data::Z &, const data::Z &>::make (integer_less), {X, Y}));

        // basic arithmetic for unbounded types.
        m = m.define (binary_operand::plus, natural_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<data::N, const data::N &, const data::N &>::make (natural_plus), {X, Y}));

        m = m.define (binary_operand::plus, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<data::Z, const data::Z &, const data::Z &>::make (integer_plus), {X, Y}));

        m = m.define (binary_operand::minus, natural_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<data::Z, const data::N &, const data::N &>::make (natural_minus), {X, Y}));

        m = m.define (binary_operand::minus, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<data::Z, const data::Z &, const data::Z &>::make (integer_times), {X, Y}));

        m = m.define (binary_operand::times, natural_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<data::N, const data::N &, const data::N &>::make (natural_times), {X, Y}));

        m = m.define (binary_operand::times, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<data::Z, const data::Z &, const data::Z &>::make (integer_times), {X, Y}));

        // casting between unbounded types
        m = m.define (symbol {"Z"}, integer_type, {natural_type, x},
            call::make (built_in_func<data::Z, const data::N &>::make (cast_natural_to_integer), {X}));

        m = m.define (symbol {"N"}, natural_type, {integer_type, x},
            call::make (built_in_func<data::N, const data::Z &>::make (cast_integer_to_natural), {X}));

        // number types that can represent bytes and chars.
        type int8_type {call::make (symbol::make ("int"), {natural::make (data::N (8))})};
        type uint8_type {call::make (symbol::make ("uint"), {natural::make (data::N (8))})};

        m = m.define (symbol {"byte"}, uint8_type);

        // mathematical operations on bytes.
        m = m.define (binary_operand::bool_equal, bool_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{uint8_type, x}, {uint8_type, y}},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<bool,
                data::int8, data::int8>::make (int8_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<bool,
                data::int8, data::int8>::make (int8_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<bool,
                data::int8, data::int8>::make (int8_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{int8_type, x}, {int8_type, y}},
            call::make (built_in_func<bool,
                data::int8, data::int8>::make (int8_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<bool,
                data::int8, data::int8>::make (int8_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<bool,
                data::int8, data::int8>::make (int8_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<bool,
                data::int8, data::int8>::make (int8_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<bool,
                data::int8, data::int8>::make (int8_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<bool,
                data::byte, data::byte>::make (uint8_greater_equal), {X, Y}));

        // bit operations on bytes.
        m = m.define (binary_operand::bit_and, uint8_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<data::byte, data::byte, data::byte>::make (uint8_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_and, int8_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<data::int8, data::int8, data::int8>::make (int8_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_or, uint8_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<data::byte, data::byte, data::byte>::make (uint8_bit_or), {X, Y}));

        m = m.define (binary_operand::bit_or, int8_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<data::int8, data::int8, data::int8>::make (int8_bit_or), {X, Y}));

        m = m.define (binary_operand::bit_xor, uint8_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<data::byte, data::byte, data::byte>::make (uint8_bit_xor), {X, Y}));

        m = m.define (binary_operand::bit_xor, int8_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<data::int8, data::int8, data::int8>::make (int8_bit_xor), {X, Y}));

        // basic arithmetic on bytes.
        m = m.define (binary_operand::plus, uint8_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<data::byte, data::byte, data::byte>::make (uint8_plus), {X, Y}));

        m = m.define (binary_operand::plus, int8_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<data::int8, data::int8, data::int8>::make (int8_plus), {X, Y}));

        m = m.define (binary_operand::minus, uint8_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<data::byte, data::byte, data::byte>::make (uint8_minus), {X, Y}));

        m = m.define (binary_operand::minus, int8_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<data::int8, data::int8, data::int8>::make (int8_times), {X, Y}));

        m = m.define (binary_operand::times, uint8_type, {uint8_type, x}, {uint8_type, y},
            call::make (built_in_func<data::byte, data::byte, data::byte>::make (uint8_times), {X, Y}));

        m = m.define (binary_operand::times, int8_type, {int8_type, x}, {int8_type, y},
            call::make (built_in_func<data::int8, data::int8, data::int8>::make (int8_times), {X, Y}));

        // some more basic number types.
        type int16_type {call::make (symbol::make ("int"), {natural::make (data::N (16))})};
        type uint16_type {call::make (symbol::make ("uint"), {natural::make (data::N (16))})};

        m = m.define (binary_operand::bool_equal, bool_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<bool,
                data::uint16, data::uint16>::make (uint16_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<bool,
                data::uint16, data::uint16>::make (uint16_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<bool,
                data::uint16, data::uint16>::make (uint16_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{uint16_type, x}, {uint16_type, y}},
            call::make (built_in_func<bool,
                data::uint16, data::uint16>::make (uint16_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<bool,
                data::int16, data::int16>::make (int16_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<bool,
                data::int16, data::int16>::make (int16_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<bool,
                data::int16, data::int16>::make (int16_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{int16_type, x}, {int16_type, y}},
            call::make (built_in_func<bool,
                data::int16, data::int16>::make (int16_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<bool,
                data::uint16, data::uint16>::make (uint16_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<bool,
                data::uint16, data::uint16>::make (uint16_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<bool,
                data::uint16, data::uint16>::make (uint16_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<bool,
                data::uint16, data::uint16>::make (uint16_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<bool,
                data::int16, data::int16>::make (int16_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<bool,
                data::int16, data::int16>::make (int16_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<bool,
                data::int16, data::int16>::make (int16_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<bool,
                data::int16, data::int16>::make (int16_less), {X, Y}));

        // bit operations on 16 bit types.
        m = m.define (binary_operand::bit_and, uint16_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<data::uint16, data::uint16, data::uint16>::make (uint16_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_and, int16_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<data::int16, data::int16, data::int16>::make (int16_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_or, uint16_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<data::uint16, data::uint16, data::uint16>::make (uint16_bit_or), {X, Y}));

        m = m.define (binary_operand::bit_or, int16_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<data::int16, data::int16, data::int16>::make (int16_bit_or), {X, Y}));

        m = m.define (binary_operand::bit_xor, uint16_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<data::uint16, data::uint16, data::uint16>::make (uint16_bit_xor), {X, Y}));

        m = m.define (binary_operand::bit_xor, int16_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<data::int16, data::int16, data::int16>::make (int16_bit_xor), {X, Y}));

        // basic arithmetic on 16 bit types.
        m = m.define (binary_operand::plus, uint16_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<data::uint16, data::uint16, data::uint16>::make (uint16_plus), {X, Y}));

        m = m.define (binary_operand::plus, int16_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<data::int16, data::int16, data::int16>::make (int16_plus), {X, Y}));

        m = m.define (binary_operand::minus, uint16_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<data::uint16, data::uint16, data::uint16>::make (uint16_minus), {X, Y}));

        m = m.define (binary_operand::minus, int16_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<data::int16, data::int16, data::int16>::make (int16_times), {X, Y}));

        m = m.define (binary_operand::times, uint16_type, {uint16_type, x}, {uint16_type, y},
            call::make (built_in_func<data::uint16, data::uint16, data::uint16>::make (uint16_times), {X, Y}));

        m = m.define (binary_operand::times, int16_type, {int16_type, x}, {int16_type, y},
            call::make (built_in_func<data::int16, data::int16, data::int16>::make (int16_times), {X, Y}));

        type int32_type {call::make (symbol::make ("int"), {natural::make (data::N (32))})};
        type uint32_type {call::make (symbol::make ("uint"), {natural::make (data::N (32))})};

        m = m.define (binary_operand::bool_equal, bool_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<bool,
                data::uint32, data::uint32>::make (uint32_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<bool,
                data::uint32, data::uint32>::make (uint32_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<bool,
                data::uint32, data::uint32>::make (uint32_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{uint32_type, x}, {uint32_type, y}},
            call::make (built_in_func<bool,
                data::uint32, data::uint32>::make (uint32_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<bool,
                data::int32, data::int32>::make (int32_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<bool,
                data::int32, data::int32>::make (int32_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<bool,
                data::int32, data::int32>::make (int32_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{int32_type, x}, {int32_type, y}},
            call::make (built_in_func<bool,
                data::int32, data::int32>::make (int32_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<bool,
                data::uint32, data::uint32>::make (uint32_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<bool,
                data::uint32, data::uint32>::make (uint32_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<bool,
                data::uint32, data::uint32>::make (uint32_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<bool,
                data::uint32, data::uint32>::make (uint32_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<bool,
                data::int32, data::int32>::make (int32_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<bool,
                data::int32, data::int32>::make (int32_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<bool,
                data::int32, data::int32>::make (int32_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<bool,
                data::int32, data::int32>::make (int32_less), {X, Y}));

        // bit operations on 32 bit types.
        m = m.define (binary_operand::bit_and, uint32_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<data::uint32, data::uint32, data::uint32>::make (uint32_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_and, int32_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<data::int32, data::int32, data::int32>::make (int32_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_or, uint32_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<data::uint32, data::uint32, data::uint32>::make (uint32_bit_or), {X, Y}));

        m = m.define (binary_operand::bit_or, int32_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<data::int32, data::int32, data::int32>::make (int32_bit_or), {X, Y}));

        m = m.define (binary_operand::bit_xor, uint32_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<data::uint32, data::uint32, data::uint32>::make (uint32_bit_xor), {X, Y}));

        m = m.define (binary_operand::bit_xor, int32_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<data::int32, data::int32, data::int32>::make (int32_bit_xor), {X, Y}));

        // basic arithmetic on 32 bit types.
        m = m.define (binary_operand::plus, uint32_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<data::uint32, data::uint32, data::uint32>::make (uint32_plus), {X, Y}));

        m = m.define (binary_operand::plus, int32_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<data::int32, data::int32, data::int32>::make (int32_plus), {X, Y}));

        m = m.define (binary_operand::minus, uint32_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<data::uint32, data::uint32, data::uint32>::make (uint32_minus), {X, Y}));

        m = m.define (binary_operand::minus, int32_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<data::int32, data::int32, data::int32>::make (int32_times), {X, Y}));

        m = m.define (binary_operand::times, uint32_type, {uint32_type, x}, {uint32_type, y},
            call::make (built_in_func<data::uint32, data::uint32, data::uint32>::make (uint32_times), {X, Y}));

        m = m.define (binary_operand::times, int32_type, {int32_type, x}, {int32_type, y},
            call::make (built_in_func<data::int32, data::int32, data::int32>::make (int32_times), {X, Y}));

        // more number types in case we need them.

        type int64_type {call::make (symbol::make ("int"), {natural::make (data::N (64))})};
        type uint64_type {call::make (symbol::make ("uint"), {natural::make (data::N (64))})};

        m = m.define (binary_operand::bool_equal, bool_type, {uint64_type, x}, {uint64_type, y},
            call::make (built_in_func<bool,
                data::uint64, data::uint64>::make (uint64_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {uint64_type, x}, {uint64_type, y},
            call::make (built_in_func<bool,
                data::uint64, data::uint64>::make (uint64_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {uint64_type, x}, {uint64_type, y},
            call::make (built_in_func<bool,
                data::uint64, data::uint64>::make (uint64_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{uint64_type, x}, {uint64_type, y}},
            call::make (built_in_func<bool,
                data::uint64, data::uint64>::make (uint64_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {int64_type, x}, {int64_type, y},
            call::make (built_in_func<bool,
                data::int64, data::int64>::make (int64_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {int64_type, x}, {int64_type, y},
            call::make (built_in_func<bool,
                data::int64, data::int64>::make (int64_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {int64_type, x}, {int64_type, y},
            call::make (built_in_func<bool,
                data::int64, data::int64>::make (int64_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{int64_type, x}, {int64_type, y}},
            call::make (built_in_func<bool,
                data::int64, data::int64>::make (int64_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint64_type, x}, {uint64_type, y},
            call::make (built_in_func<bool,
                data::uint64, data::uint64>::make (uint64_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {uint64_type, x}, {uint64_type, y},
            call::make (built_in_func<bool,
                data::uint64, data::uint64>::make (uint64_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {uint64_type, x}, {uint64_type, y},
            call::make (built_in_func<bool,
                data::uint64, data::uint64>::make (uint64_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {uint64_type, x}, {uint64_type, y},
            call::make (built_in_func<bool,
                data::uint64, data::uint64>::make (uint64_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {int64_type, x}, {int64_type, y},
            call::make (built_in_func<bool,
                data::int64, data::int64>::make (int64_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {int64_type, x}, {int64_type, y},
            call::make (built_in_func<bool,
                data::int64, data::int64>::make (int64_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {int64_type, x}, {int64_type, y},
            call::make (built_in_func<bool,
                data::int64, data::int64>::make (int64_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {int64_type, x}, {int64_type, y},
            call::make (built_in_func<bool,
                data::int64, data::int64>::make (int64_less), {X, Y}));

        type int128_type {call::make (symbol::make ("int"), {natural::make (data::N (128))})};
        type uint128_type {call::make (symbol::make ("uint"), {natural::make (data::N (128))})};

        m = m.define (binary_operand::bool_equal, bool_type, {uint128_type, x}, {uint128_type, y},
            call::make (built_in_func<bool,
                const data::uint128 &, const data::uint128 &>::make (uint128_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {uint128_type, x}, {uint128_type, y},
            call::make (built_in_func<bool,
                const data::uint128 &, const data::uint128 &>::make (uint128_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {uint128_type, x}, {uint128_type, y},
            call::make (built_in_func<bool,
                const data::uint128 &, const data::uint128 &>::make (uint128_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{uint128_type, x}, {uint128_type, y}},
            call::make (built_in_func<bool,
                const data::uint128 &, const data::uint128 &>::make (uint128_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {int128_type, x}, {int128_type, y},
            call::make (built_in_func<bool,
                const data::int128 &, const data::int128 &>::make (int128_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {int128_type, x}, {int128_type, y},
            call::make (built_in_func<bool,
                const data::int128 &, const data::int128 &>::make (int128_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {int128_type, x}, {int128_type, y},
            call::make (built_in_func<bool,
                const data::int128 &, const data::int128 &>::make (int128_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{int128_type, x}, {int128_type, y}},
            call::make (built_in_func<bool,
                const data::int128 &, const data::int128 &>::make (int128_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint128_type, x}, {uint128_type, y},
            call::make (built_in_func<bool,
                const data::uint128 &, const data::uint128 &>::make (uint128_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {uint128_type, x}, {uint128_type, y},
            call::make (built_in_func<bool,
                const data::uint128 &, const data::uint128 &>::make (uint128_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {uint128_type, x}, {uint128_type, y},
            call::make (built_in_func<bool,
                const data::uint128 &, const data::uint128 &>::make (uint128_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {uint128_type, x}, {uint128_type, y},
            call::make (built_in_func<bool,
                const data::uint128 &, const data::uint128 &>::make (uint128_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {int128_type, x}, {int128_type, y},
            call::make (built_in_func<bool,
                const data::int128 &, const data::int128 &>::make (int128_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {int128_type, x}, {int128_type, y},
            call::make (built_in_func<bool,
                const data::int128 &, const data::int128 &>::make (int128_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {int128_type, x}, {int128_type, y},
            call::make (built_in_func<bool,
                const data::int128 &, const data::int128 &>::make (int128_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {int128_type, x}, {int128_type, y},
            call::make (built_in_func<bool,
                const data::int128 &, const data::int128 &>::make (int128_less), {X, Y}));

        type int160_type {call::make (symbol::make ("int"), {natural::make (data::N (160))})};
        type uint160_type {call::make (symbol::make ("uint"), {natural::make (data::N (160))})};

        m = m.define (binary_operand::bool_equal, bool_type, {uint160_type, x}, {uint160_type, y},
            call::make (built_in_func<bool,
                const data::uint160 &, const data::uint160 &>::make (uint160_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {uint160_type, x}, {uint160_type, y},
            call::make (built_in_func<bool,
                const data::uint160 &, const data::uint160 &>::make (uint160_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {uint160_type, x}, {uint160_type, y},
            call::make (built_in_func<bool,
                const data::uint160 &, const data::uint160 &>::make (uint160_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{uint160_type, x}, {uint160_type, y}},
            call::make (built_in_func<bool,
                const data::uint160 &, const data::uint160 &>::make (uint160_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {int160_type, x}, {int160_type, y},
            call::make (built_in_func<bool,
                const data::int160 &, const data::int160 &>::make (int160_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {int160_type, x}, {int160_type, y},
            call::make (built_in_func<bool,
                const data::int160 &, const data::int160 &>::make (int160_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {int160_type, x}, {int160_type, y},
            call::make (built_in_func<bool,
                const data::int160 &, const data::int160 &>::make (int160_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{int160_type, x}, {int160_type, y}},
            call::make (built_in_func<bool,
                const data::int160 &, const data::int160 &>::make (int160_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint160_type, x}, {uint160_type, y},
            call::make (built_in_func<bool,
                const data::uint160 &, const data::uint160 &>::make (uint160_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {uint160_type, x}, {uint160_type, y},
            call::make (built_in_func<bool,
                const data::uint160 &, const data::uint160 &>::make (uint160_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {uint160_type, x}, {uint160_type, y},
            call::make (built_in_func<bool,
                const data::uint160 &, const data::uint160 &>::make (uint160_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {uint160_type, x}, {uint160_type, y},
            call::make (built_in_func<bool,
                const data::uint160 &, const data::uint160 &>::make (uint160_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {int160_type, x}, {int160_type, y},
            call::make (built_in_func<bool,
                const data::int160 &, const data::int160 &>::make (int160_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {int160_type, x}, {int160_type, y},
            call::make (built_in_func<bool,
                const data::int160 &, const data::int160 &>::make (int160_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {int160_type, x}, {int160_type, y},
            call::make (built_in_func<bool,
                const data::int160 &, const data::int160 &>::make (int160_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {int160_type, x}, {int160_type, y},
            call::make (built_in_func<bool,
                const data::int160 &, const data::int160 &>::make (int160_less), {X, Y}));

        type int256_type {call::make (symbol::make ("int"), {natural::make (data::N (256))})};
        type uint256_type {call::make (symbol::make ("uint"), {natural::make (data::N (256))})};

        m = m.define (binary_operand::bool_equal, bool_type, {uint256_type, x}, {uint256_type, y},
            call::make (built_in_func<bool,
                const data::uint256 &, const data::uint256 &>::make (uint256_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {uint256_type, x}, {uint256_type, y},
            call::make (built_in_func<bool,
                const data::uint256 &, const data::uint256 &>::make (uint256_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {uint256_type, x}, {uint256_type, y},
            call::make (built_in_func<bool,
                const data::uint256 &, const data::uint256 &>::make (uint256_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{uint256_type, x}, {uint256_type, y}},
            call::make (built_in_func<bool,
                const data::uint256 &, const data::uint256 &>::make (uint256_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {int256_type, x}, {int256_type, y},
            call::make (built_in_func<bool,
                const data::int256 &, const data::int256 &>::make (int256_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {int256_type, x}, {int256_type, y},
            call::make (built_in_func<bool,
                const data::int256 &, const data::int256 &>::make (int256_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {int256_type, x}, {int256_type, y},
            call::make (built_in_func<bool,
                const data::int256 &, const data::int256 &>::make (int256_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{int256_type, x}, {int256_type, y}},
            call::make (built_in_func<bool,
                const data::int256 &, const data::int256 &>::make (int256_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint256_type, x}, {uint256_type, y},
            call::make (built_in_func<bool,
                const data::uint256 &, const data::uint256 &>::make (uint256_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {uint256_type, x}, {uint256_type, y},
            call::make (built_in_func<bool,
                const data::uint256 &, const data::uint256 &>::make (uint256_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {uint256_type, x}, {uint256_type, y},
            call::make (built_in_func<bool,
                const data::uint256 &, const data::uint256 &>::make (uint256_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {uint256_type, x}, {uint256_type, y},
            call::make (built_in_func<bool,
                const data::uint256 &, const data::uint256 &>::make (uint256_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {int256_type, x}, {int256_type, y},
            call::make (built_in_func<bool,
                const data::int256 &, const data::int256 &>::make (int256_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {int256_type, x}, {int256_type, y},
            call::make (built_in_func<bool,
                const data::int256 &, const data::int256 &>::make (int256_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {int256_type, x}, {int256_type, y},
            call::make (built_in_func<bool,
                const data::int256 &, const data::int256 &>::make (int256_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {int256_type, x}, {int256_type, y},
            call::make (built_in_func<bool,
                const data::int256 &, const data::int256 &>::make (int256_less), {X, Y}));

        type int512_type {call::make (symbol::make ("int"), {natural::make (data::N (512))})};
        type uint512_type {call::make (symbol::make ("uint"), {natural::make (data::N (512))})};

        m = m.define (binary_operand::bool_equal, bool_type, {uint512_type, x}, {uint512_type, y},
            call::make (built_in_func<bool,
                const data::uint512 &, const data::uint512 &>::make (uint512_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {uint512_type, x}, {uint512_type, y},
            call::make (built_in_func<bool,
                const data::uint512 &, const data::uint512 &>::make (uint512_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {uint512_type, x}, {uint512_type, y},
            call::make (built_in_func<bool,
                const data::uint512 &, const data::uint512 &>::make (uint512_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{uint512_type, x}, {uint512_type, y}},
            call::make (built_in_func<bool,
                const data::uint512 &, const data::uint512 &>::make (uint512_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {int512_type, x}, {int512_type, y},
            call::make (built_in_func<bool,
                const data::int512 &, const data::int512 &>::make (int512_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {int512_type, x}, {int512_type, y},
            call::make (built_in_func<bool,
                const data::int512 &, const data::int512 &>::make (int512_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {int512_type, x}, {int512_type, y},
            call::make (built_in_func<bool,
                const data::int512 &, const data::int512 &>::make (int512_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{int512_type, x}, {int512_type, y}},
            call::make (built_in_func<bool,
                const data::int512 &, const data::int512 &>::make (int512_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {uint512_type, x}, {uint512_type, y},
            call::make (built_in_func<bool,
                const data::uint512 &, const data::uint512 &>::make (uint512_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {uint512_type, x}, {uint512_type, y},
            call::make (built_in_func<bool,
                const data::uint512 &, const data::uint512 &>::make (uint512_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {uint512_type, x}, {uint512_type, y},
            call::make (built_in_func<bool,
                const data::uint512 &, const data::uint512 &>::make (uint512_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {uint512_type, x}, {uint512_type, y},
            call::make (built_in_func<bool,
                const data::uint512 &, const data::uint512 &>::make (uint512_less), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {int512_type, x}, {int512_type, y},
            call::make (built_in_func<bool,
                const data::int512 &, const data::int512 &>::make (int512_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {int512_type, x}, {int512_type, y},
            call::make (built_in_func<bool,
                const data::int512 &, const data::int512 &>::make (int512_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {int512_type, x}, {int512_type, y},
            call::make (built_in_func<bool,
                const data::int512 &, const data::int512 &>::make (int512_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {int512_type, x}, {int512_type, y},
            call::make (built_in_func<bool,
                const data::int512 &, const data::int512 &>::make (int512_less), {X, Y}));

        // Size for fixed size number types.
        m = m.define (symbol {"size"}, natural_type, {uint8_type}, natural::make (1));
        m = m.define (symbol {"size"}, natural_type, {int8_type}, natural::make (1));
        m = m.define (symbol {"size"}, natural_type, {uint16_type}, natural::make (2));
        m = m.define (symbol {"size"}, natural_type, {int16_type}, natural::make (2));
        m = m.define (symbol {"size"}, natural_type, {uint32_type}, natural::make (4));
        m = m.define (symbol {"size"}, natural_type, {int32_type}, natural::make (4));
        m = m.define (symbol {"size"}, natural_type, {uint64_type}, natural::make (8));
        m = m.define (symbol {"size"}, natural_type, {int64_type}, natural::make (8));
        m = m.define (symbol {"size"}, natural_type, {uint128_type}, natural::make (16));
        m = m.define (symbol {"size"}, natural_type, {int128_type}, natural::make (16));
        m = m.define (symbol {"size"}, natural_type, {uint160_type}, natural::make (20));
        m = m.define (symbol {"size"}, natural_type, {int160_type}, natural::make (20));
        m = m.define (symbol {"size"}, natural_type, {uint256_type}, natural::make (32));
        m = m.define (symbol {"size"}, natural_type, {int256_type}, natural::make (32));
        m = m.define (symbol {"size"}, natural_type, {uint512_type}, natural::make (64));
        m = m.define (symbol {"size"}, natural_type, {int512_type}, natural::make (64));

        // we do not have a char type right now. A char type would
        // naturally be based on a uint32, as strings will be unicode.
        type bytes_type {symbol::make ("bytes")};
        type string_type {symbol::make ("string")};

        m = m.define (binary_operand::identical, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_func<bool,
                const data::string &, const data::string &>::make (string_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{string_type, x}, {string_type, y}},
            call::make (built_in_func<bool,
                const data::string &, const data::string &>::make (&string_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_func<bool,
                const data::string &, const data::string &>::make (string_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_func<bool,
                const data::string &, const data::string &>::make (string_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {bytes_type, x}, {bytes_type, y},
            call::make (built_in_func<bool,
                const data::bytes &, const data::bytes &>::make (bytes_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{bytes_type, x}, {bytes_type, y}},
            call::make (built_in_func<bool,
                const data::bytes &, const data::bytes &>::make (bytes_equal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {bytes_type, x}, {bytes_type, y},
            call::make (built_in_func<bool,
                const data::bytes &, const data::bytes &>::make (bytes_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {bytes_type, x}, {bytes_type, y},
            call::make (built_in_func<bool,
                const data::bytes &, const data::bytes &>::make (bytes_unequal), {X, Y}));

        // size for string and bytes.
        m = m.define (symbol {"size"}, natural_type, {{bytes_type, x}},
            call::make (built_in_func<data::N,
                const data::bytes &>::make (&bytes_size), {X}));

        m = m.define (symbol {"size"}, natural_type, {{string_type, x}},
            call::make (built_in_func<data::N,
                const data::string &>::make (&string_size), {X}));

        // cat for string and bytes.
        m = m.define (binary_operand::cat, string_type, {string_type, x}, {string_type, y},
            call::make (built_in_func<data::string,
                const data::string &, const data::string &>::make (string_cat), {X, Y}));

        m = m.define (binary_operand::cat, bytes_type, {bytes_type, x}, {bytes_type, y},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (bytes_cat), {X, Y}));

        m = m.define (symbol ("cat"), string_type, {{string_type, x}, {string_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const data::string &>::make (&string_cat), {X, Y}));

        m = m.define (symbol ("cat"), bytes_type, {{bytes_type, x}, {bytes_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (&bytes_cat), {X, Y}));

        // bitcoin numbers. We have scriptnum, an unbounded integer type represented
        // as a byte array and fixed size uint_little types for a variety of sizes.

        type scriptnum_type {call::make (symbol::make ("scriptnum"), {bytes_type})};

        auto scriptnum_pattern = [&] (Symbol z) -> pattern {
            return call::make (symbol::make ("scriptnum"), {pattern {bytes_type, z}});
        };

        auto uint_little_type = [&] (const data::N &n) -> type {
            return call::make (call::make (symbol::make ("uint_little"), {natural::make (n)}), {bytes_type});
        };

        auto uint_little_pattern = [&] (const data::N &n, Symbol x) -> type {
            return call::make (call::make (symbol::make ("uint_little"), {natural::make (n)}), {pattern {bytes_type, x}});
        };

        // bitcoin bit operations
        m = m.define (unary_operand::tilda, scriptnum_type,
            scriptnum_pattern (x),
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes,
                    const data::bytes &>::make (scriptnum_bit_not), {X})}));

        m = m.define (symbol {"bit_not"}, scriptnum_type,
            {scriptnum_pattern (x)},
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes,
                    const data::bytes &>::make (scriptnum_bit_not), {X})}));

        m = m.define (binary_operand::bit_and, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bit_and), {X, Y})}));

        m = m.define (symbol {"bit_and"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bit_and), {X, Y})}));

        m = m.define (binary_operand::bit_or, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bit_or), {X, Y})}));

        m = m.define (symbol {"bit_or"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bit_or), {X, Y})}));

        m = m.define (binary_operand::bit_xor, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bit_xor), {X, Y})}));

        m = m.define (symbol {"bit_xor"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bit_xor), {X, Y})}));

        // scriptnum boolean operations
        m = m.define (unary_operand::bool_not, scriptnum_type,
            scriptnum_pattern (x),
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes,
                    const data::bytes &>::make (scriptnum_bool_not), {X})}));

        m = m.define (symbol {"not"}, scriptnum_type,
            {scriptnum_pattern (x)},
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes,
                    const data::bytes &>::make (scriptnum_bool_not), {X})}));

        m = m.define (binary_operand::bool_and, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes,
                    const data::bytes &, const data::bytes &>::make (scriptnum_bool_and), {X, Y})}));

        m = m.define (symbol {"and"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bool_and), {X, Y})}));

        m = m.define (binary_operand::bool_or, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bool_or), {X, Y})}));

        m = m.define (symbol {"or"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_bool_or), {X, Y})}));

        // identical
        m = m.define (binary_operand::identical, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_identical), {X, Y})}));

        m = m.define (symbol {"identical"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_identical), {X, Y})}));

        // comparisons
        m = m.define (binary_operand::bool_equal, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_equal), {X, Y})}));

        m = m.define (binary_operand::bool_unequal, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_unequal), {X, Y})}));

        m = m.define (binary_operand::greater_equal, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_greater_equal), {X, Y})}));

        m = m.define (binary_operand::less_equal, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_less_equal), {X, Y})}));

        m = m.define (binary_operand::greater, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_greater), {X, Y})}));

        m = m.define (binary_operand::less, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_less), {X, Y})}));

        // cast scriptnum to bool.
        m = m.define (symbol {"bool"}, bool_type,
            {scriptnum_pattern (x)},
            call::make (built_in_func<bool, const data::bytes &>::make (scriptnum_cast_to_bool), {X}));

        // basic arithmetic for bitcoin numbers.
        m = m.define (binary_operand::plus, scriptnum_type,
            scriptnum_pattern (x), scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_plus), {X, Y})}));

        m = m.define (binary_operand::minus, scriptnum_type,
            scriptnum_pattern (x), scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_minus), {X, Y})}));

        m = m.define (binary_operand::times, scriptnum_type,
            scriptnum_pattern (x), scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_times), {X, Y})}));

        m = m.define (binary_operand::divide, scriptnum_type,
            scriptnum_pattern (x), scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_divide), {X, Y})}));

        m = m.define (binary_operand::mod, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (scriptnum_mod), {X, Y})}));

        // casting between number types.
        m = m.define (symbol {"scriptnum"}, scriptnum_type, {pattern {natural_type, x}},
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes, const data::N &>::make (cast_N_to_scriptnum), {X})}));

        m = m.define (symbol {"scriptnum"}, scriptnum_type, {pattern {integer_type, x}},
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes, const data::Z &>::make (cast_Z_to_scriptnum), {X})}));

        m = m.define (symbol {"Z"}, integer_type,
            {scriptnum_pattern (x)},
                call::make (built_in_func<data::Z, const data::bytes &>::make (cast_scriptnum_to_Z), {X}));

        m = m.define (symbol {"N"}, natural_type,
            {scriptnum_pattern (x)},
                call::make (built_in_func<data::N, const data::bytes &>::make (cast_scriptnum_to_N), {X}));

        // TODO indexing for bitcoin number types.

        // size and indexing. We have many types that support indexing.
        // we do not have a special char type for strings but we use a uint32 because
        // it's unicode.
        m = m.define (binary_operand::dot, uint8_type, {bytes_type, x}, {natural_type, y},
            call::make (built_in_func<data::byte,
                const data::bytes &, const data::N &>::make (bytes_get), {X, Y}));

        m = m.define (binary_operand::dot, uint32_type, {string_type, x}, {natural_type, y},
            call::make (built_in_func<data::uint32,
                const data::string &, const data::N &>::make (string_get), {X, Y}));

        m = m.define (binary_operand::dot, uint8_type, {bytes_type, x},
            scriptnum_pattern (y),
            call::make (built_in_func<data::byte,
                const data::bytes &, const Bitcoin::integer &>::make (bytes_get), {X, Y}));

        m = m.define (binary_operand::dot, uint32_type, {string_type, x},
            scriptnum_pattern (y),
            call::make (built_in_func<data::uint32,
                const data::string &, const Bitcoin::integer &>::make (string_get), {X, Y}));

        m = m.define (binary_operand::dot, uint8_type,
            scriptnum_pattern (x), {natural_type, y},
            call::make (built_in_func<data::byte,
                const data::bytes &, const data::N &>::make (bytes_get), {X, Y}));

        m = m.define (binary_operand::dot, uint8_type,
            scriptnum_pattern (x), scriptnum_pattern (y),
            call::make (built_in_func<data::byte,
                const data::bytes &, const Bitcoin::integer &>::make (bytes_get), {X, Y}));

        // size operations for scriptnum
        m = m.define (symbol {"size"}, scriptnum_type,
            {scriptnum_pattern (x)},
            call::make (symbol::make ("scriptnum"),
                {call::make (built_in_func<data::bytes, const data::bytes &>::make (&scriptnum_size), {X})}));

        m = m.define (symbol {"minimal_size"}, scriptnum_type,
            {scriptnum_pattern (x)},
            call::make (symbol::make ("scriptnum"),
                {call::make (built_in_func<data::bytes, const data::bytes &>::make (&scriptnum_minimal_size), {X})}));

        m = m.define (symbol {"minimize"}, scriptnum_type,
            {scriptnum_pattern (x)},
            call::make (symbol::make ("scriptnum"),
                {call::make (built_in_func<data::bytes, const data::bytes &>::make (&scriptnum_minimize), {X})}));

        m = m.define (symbol {"minimal"}, bool_type,
            {scriptnum_pattern (x)},
            call::make (symbol::make ("scriptnum"),
                {call::make (built_in_func<bool, const data::bytes &>::make (&scriptnum_minimal), {X})}));

        m = m.define (symbol {"resize"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"),
                    {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (&scriptnum_resize), {X, Y})}));

        m = m.define (symbol {"resize"}, scriptnum_type,
            {scriptnum_pattern (x), {natural_type, y}},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::N &>::make (&scriptnum_resize), {X, Y})}));

        // Basic string operations for string and bytes.
        m = m.define (symbol {"left"}, bytes_type,
            {{bytes_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const Bitcoin::integer &>::make (&bytes_left), {X, Y}));

        m = m.define (symbol {"left"}, bytes_type,
            {{bytes_type, x}, {integer_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const data::N &>::make (&bytes_left), {X, Y}));

        m = m.define (symbol {"left"}, string_type,
            {{string_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const Bitcoin::integer &>::make (&string_left), {X, Y}));

        m = m.define (symbol {"left"}, string_type,
            {{string_type, x}, {integer_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const data::N &>::make (&string_left), {X, Y}));

        m = m.define (symbol {"right"}, bytes_type,
            {{bytes_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const Bitcoin::integer &>::make (&bytes_right), {X, Y}));

        m = m.define (symbol {"right"}, bytes_type,
            {{bytes_type, x}, {integer_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const data::N &>::make (&bytes_right), {X, Y}));

        m = m.define (symbol {"right"}, string_type,
            {{string_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const Bitcoin::integer &>::make (&string_right), {X, Y}));

        m = m.define (symbol {"right"}, string_type,
            {{string_type, x}, {integer_type, y}},
            call::make (built_in_func<data::string,
                const data::string &, const data::N &>::make (&string_right), {X, Y}));

        m = m.define (symbol {"split"}, list::make ({bytes_type, bytes_type}),
            {{bytes_type, x}, {integer_type, y}},
            call::make (built_in_func<std::tuple<data::bytes, data::bytes>,
                const data::bytes &, const Bitcoin::integer &>::make (&bytes_split), {X, Y}));

        m = m.define (symbol {"split"}, list::make ({bytes_type, bytes_type}),
            {{bytes_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<std::tuple<data::bytes, data::bytes>,
                const data::bytes &, const data::N &>::make (&bytes_split), {X, Y}));

        m = m.define (symbol {"split"}, list::make ({string_type, string_type}),
            {{string_type, x}, {integer_type, y}},
            call::make (built_in_func<std::tuple<data::string, data::string>,
                const data::string &, const Bitcoin::integer &>::make (&string_split), {X, Y}));

        m = m.define (symbol {"split"}, list::make ({string_type, string_type}),
            {{string_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<std::tuple<data::string, data::string>,
                const data::string &, const data::N &>::make (&string_split), {X, Y}));

        // we also have secret and coord, two modular number types that are used in the
        // Bitcoin elliptic curve.

        type coord_type {call::make (symbol::make ("coord"), {natural_type})};
        type secret_type {call::make (symbol::make ("secret"), {natural_type})};

        m = m.define (symbol {"Coordinate"}, expression {coord_type});
        m = m.define (symbol {"Secret"}, expression {secret_type});

        // identical
        m = m.define (binary_operand::identical, bool_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type,
            {call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
                call::make (symbol::make ("coord"), {pattern {natural_type, y}})},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_equal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (secret_equal), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type,
            {call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
                call::make (symbol::make ("secret"), {pattern {natural_type, y}})},
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (secret_equal), {X, Y}));

        // comparisons for coordinates
        m = m.define (binary_operand::bool_equal, bool_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_unequal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_less), {X, Y}));

        // comparisons for secrets
        m = m.define (binary_operand::bool_equal, bool_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_equal), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_unequal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (built_in_func<bool,
                const data::N &, const data::N &>::make (coord_less), {X, Y}));

        // ` operator (used in key derivations)

        m = m.define (unary_operand::harden, uint8_type, {uint8_type, x},
            call::make (built_in_func<data::byte, data::byte>::make (harden), {X}));

        m = m.define (unary_operand::harden, uint16_type, {uint16_type, x},
            call::make (built_in_func<data::uint16, data::uint16>::make (harden), {X}));

        m = m.define (unary_operand::harden, uint32_type, {uint32_type, x},
            call::make (built_in_func<data::uint32, data::uint32>::make (harden), {X}));

        m = m.define (unary_operand::harden, uint64_type, {uint64_type, x},
            call::make (built_in_func<data::uint64, data::uint64>::make (harden), {X}));

        m = m.define (unary_operand::harden, uint128_type, {uint128_type, x},
            call::make (built_in_func<data::uint128, const data::uint128 &>::make (harden), {X}));

        m = m.define (unary_operand::harden, uint160_type, {uint160_type, x},
            call::make (built_in_func<data::uint160, const data::uint160 &>::make (harden), {X}));

        m = m.define (unary_operand::harden, uint256_type, {uint256_type, x},
            call::make (built_in_func<data::uint256, const data::uint256 &>::make (harden), {X}));

        m = m.define (unary_operand::harden, uint512_type, {uint512_type, x},
            call::make (built_in_func<data::uint512, const data::uint512 &>::make (harden), {X}));

        // set sign bit.
        m = m.define (unary_operand::harden, scriptnum_type,
            scriptnum_pattern (x),
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes, const data::bytes &>::make (set_sign_bit), {X})}));

        // TODO Let's do some casts

        // N can be cast to any other number type.
        // Z can be cast to any other integer type.

        // bool can be cast to scriptnum.

        // bytes can be cast to scriptnum.

        // string operations for scriptnum
        m = m.define (binary_operand::cat, scriptnum_type,
            scriptnum_pattern (x),
            scriptnum_pattern (y),
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::bytes &>::make (&bytes_cat), {X, Y})}));

        m = m.define (symbol {"left"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const Bitcoin::integer &>::make (&bytes_left), {X, Y})}));

        m = m.define (symbol {"right"}, scriptnum_type,
            {scriptnum_pattern (x),
                scriptnum_pattern (y)},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const Bitcoin::integer &>::make (&bytes_right), {X, Y})}));

        // TODO: scriptnum split. Not sure how to do this one yet.
        m = m.declare (symbol {"split"}, list::make ({scriptnum_type, scriptnum_type}),
            {{scriptnum_type, x}, {scriptnum_type, y}});

        // bit shifts
        m = m.define (symbol {"right_shift"}, bytes_type,
            {{bytes_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const Bitcoin::integer &>::make (&bytes_right_shift), {X, Y}));

        m = m.define (symbol {"left_shift"}, bytes_type,
            {{bytes_type, x}, {scriptnum_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const Bitcoin::integer &>::make (&bytes_left_shift), {X, Y}));

        m = m.define (symbol {"right_shift"}, bytes_type,
            {{bytes_type, x}, {integer_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const data::N &>::make (&bytes_right_shift), {X, Y}));

        m = m.define (symbol {"left_shift"}, bytes_type,
            {{bytes_type, x}, {integer_type, y}},
            call::make (built_in_func<data::bytes,
                const data::bytes &, const data::N &>::make (&bytes_left_shift), {X, Y}));

        // TODO and bit shift for scriptnum.

        // let's start doing arithmetic with all these number types.

        // modular arithmetic
        m = m.define (binary_operand::mod, natural_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<data::N, const data::N &, const data::N &>::make (natural_mod), {X, Y}));

        m = m.define (binary_operand::mod, natural_type, {integer_type, x}, {natural_type, y},
            call::make (built_in_func<data::N, const data::Z &, const data::N &>::make (integer_mod), {X, Y}));

        m = m.define (symbol {"mod"}, natural_type, {{natural_type, x}, {natural_type, y}},
            call::make (built_in_func<data::N, const data::N &, const data::N &>::make (natural_mod), {X, Y}));

        m = m.define (symbol {"mod"}, natural_type, {{integer_type, x}, {natural_type, y}},
            call::make (built_in_func<data::N, const data::Z &, const data::N &>::make (integer_mod), {X, Y}));

        m = m.define (symbol {"plus_mod"}, natural_type, {{natural_type, x}, {natural_type, y}, {natural_type, z}},
            call::make (built_in_func<data::N, const data::N &, const data::N &, const data::N &>::make (natural_plus_mod), {X, Y, Z}));

        m = m.define (symbol {"plus_mod"}, natural_type, {{integer_type, x}, {integer_type, y}, {natural_type, z}},
            call::make (built_in_func<data::N, const data::Z &, const data::Z &, const data::N &>::make (integer_plus_mod), {X, Y, Z}));

        m = m.define (symbol {"minus_mod"}, natural_type, {{natural_type, x}, {natural_type, y}, {natural_type, z}},
            call::make (built_in_func<data::N, const data::N &, const data::N &, const data::N &>::make (natural_minus_mod), {X, Y, Z}));

        m = m.define (symbol {"minus_mod"}, natural_type, {{integer_type, x}, {integer_type, y}, {natural_type, z}},
            call::make (built_in_func<data::N, const data::Z &, const data::Z &, const data::N &>::make (integer_minus_mod), {X, Y, Z}));

        m = m.define (symbol {"times_mod"}, natural_type, {{natural_type, x}, {natural_type, y}, {natural_type, z}},
            call::make (built_in_func<data::N, const data::N &, const data::N &, const data::N &>::make (natural_times_mod), {X, Y, Z}));

        m = m.define (symbol {"times_mod"}, natural_type, {{integer_type, x}, {integer_type, y}, {natural_type, z}},
            call::make (built_in_func<data::N, const data::Z &, const data::Z &, const data::N &>::make (integer_times_mod), {X, Y, Z}));

        // TODO invert_mod?

        // plus_mod, minus_mod, times_mod, and invert_mod for scriptnum

        // here's abs and negate.

        m = m.define (symbol ("abs"), uint8_type, {{uint8_type, x}}, X);

        m = m.define (symbol ("negate"), uint8_type, {{uint8_type, x}},
            call::make (built_in_func<data::byte, data::byte>::make (uint8_negate), {X}));

        m = m.define (unary_operand::negate, uint8_type, {uint8_type, x},
            call::make (built_in_func<data::byte, data::byte>::make (uint8_negate), {X}));

        m = m.define (symbol ("abs"), uint8_type, {{int8_type, x}},
            call::make (built_in_func<data::int8, data::int8>::make (int8_abs), {X}));

        m = m.define (symbol ("negate"), int8_type, {{int8_type, x}},
            call::make (built_in_func<data::int8, data::int8>::make (int8_negate), {X}));

        m = m.define (unary_operand::negate, int8_type, {int8_type, x},
            call::make (built_in_func<data::int8, data::int8>::make (int8_negate), {X}));

        m = m.define (symbol ("abs"), uint16_type, {{uint16_type, x}}, X);

        m = m.define (symbol ("negate"), uint16_type, {{uint16_type, x}},
            call::make (built_in_func<data::uint16, data::uint16>::make (uint16_negate), {X}));

        m = m.define (unary_operand::negate, uint16_type, {uint16_type, x},
            call::make (built_in_func<data::uint16, data::uint16>::make (uint16_negate), {X}));

        m = m.define (symbol ("abs"), uint16_type, {{int16_type, x}},
            call::make (built_in_func<data::int16, data::int16>::make (int16_abs), {X}));

        m = m.define (symbol ("negate"), int16_type, {{int16_type, x}},
            call::make (built_in_func<data::int16, data::int16>::make (int16_negate), {X}));

        m = m.define (unary_operand::negate, int16_type, {int16_type, x},
            call::make (built_in_func<data::int16, data::int16>::make (int16_negate), {X}));

        m = m.define (symbol ("abs"), uint32_type, {{uint32_type, x}}, X);

        m = m.define (symbol ("negate"), uint32_type, {{uint32_type, x}},
            call::make (built_in_func<data::uint32, data::uint32>::make (uint32_negate), {X}));

        m = m.define (unary_operand::negate, uint32_type, {uint32_type, x},
            call::make (built_in_func<data::uint32, data::uint32>::make (uint32_negate), {X}));

        m = m.define (symbol ("abs"), int32_type, {{int32_type, x}},
            call::make (built_in_func<data::int32, data::int32>::make (int32_abs), {X}));

        m = m.define (symbol ("negate"), int32_type, {{int32_type, x}},
            call::make (built_in_func<data::int32, data::int32>::make (int32_negate), {X}));

        m = m.define (unary_operand::negate, int32_type, {int32_type, x},
            call::make (built_in_func<data::int32, data::int32>::make (int32_negate), {X}));

        m = m.define (symbol ("abs"), uint64_type, {{uint64_type, x}}, X);

        m = m.define (symbol ("negate"), uint64_type, {{uint64_type, x}},
            call::make (built_in_func<data::uint64, data::uint64>::make (uint64_negate), {X}));

        m = m.define (unary_operand::negate, uint64_type, {uint64_type, x},
            call::make (built_in_func<data::uint64, data::uint64>::make (uint64_negate), {X}));

        m = m.define (symbol ("abs"), uint64_type, {{int64_type, x}},
            call::make (built_in_func<data::int64, data::int64>::make (int64_abs), {X}));

        m = m.define (symbol ("negate"), int64_type, {{int64_type, x}},
            call::make (built_in_func<data::int64, data::int64>::make (int64_negate), {X}));

        m = m.define (unary_operand::negate, int64_type, {int64_type, x},
            call::make (built_in_func<data::int64, data::int64>::make (int64_negate), {X}));

        // abs and negate for unbouned numbers.
        m = m.define (symbol ("abs"), natural_type, {{natural_type, x}}, X);

        m = m.define (symbol ("negate"), integer_type, {{natural_type, x}},
            call::make (built_in_func<data::Z, const data::N &>::make (natural_negate), {X}));

        m = m.define (unary_operand::negate, integer_type, {natural_type, x},
            call::make (built_in_func<data::Z, const data::N &>::make (natural_negate), {X}));

        m = m.define (symbol ("abs"), natural_type, {{integer_type, x}},
            call::make (built_in_func<data::N, const data::Z &>::make (integer_abs), {X}));

        m = m.define (symbol ("negate"), integer_type, {{integer_type, x}},
            call::make (built_in_func<data::Z, const data::Z &>::make (integer_negate), {X}));

        m = m.define (unary_operand::negate, integer_type, {integer_type, x},
            call::make (built_in_func<data::Z, const data::Z &>::make (integer_negate), {X}));

        // abs and negate for scriptnum.
        m = m.define (symbol ("abs"), scriptnum_type,
            {scriptnum_pattern (x)},
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes,
                    const data::bytes &>::make (scriptnum_abs), {X})}));

        m = m.define (symbol ("negate"), scriptnum_type,
            {scriptnum_pattern (x)},
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes,
                    const data::bytes &>::make (scriptnum_negate), {X})}));

        m = m.define (unary_operand::negate, scriptnum_type,
            scriptnum_pattern (x),
            call::make (symbol::make ("scriptnum"), {
                call::make (built_in_func<data::bytes,
                    const data::bytes &>::make (scriptnum_negate), {X})}));

        // abs and negate for coordinate and secret.
        m = m.define (symbol ("abs"), secret_type,
            {call::make (symbol::make ("secret"), {pattern {natural_type, x}})},
            call::make (symbol::make ("secret"), {X}));

        m = m.define (symbol ("negate"), secret_type,
            {call::make (symbol::make ("secret"), {pattern {natural_type, x}})},
            call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &>::make (&secret_negate), {X})}));

        m = m.define (unary_operand::negate, secret_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &>::make (&secret_negate), {X})}));

        m = m.define (symbol ("abs"), coord_type,
            {call::make (symbol::make ("coord"), {pattern {natural_type, x}})},
            call::make (symbol::make ("coord"), {X}));

        m = m.define (symbol ("negate"), coord_type,
            {call::make (symbol::make ("coord"), {pattern {natural_type, x}})},
            call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &>::make (coord_negate), {X})}));

        m = m.define (unary_operand::negate, coord_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &>::make (coord_negate), {X})}));

        // arithmetic for coordinates
        m = m.define (binary_operand::plus, coord_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (coord_plus), {X, Y})}));

        m = m.define (binary_operand::minus, coord_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (coord_minus), {X, Y})}));

        m = m.define (binary_operand::times, coord_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (coord_times), {X, Y})}));

        m = m.define (symbol {"invert"}, coord_type,
            {call::make (symbol::make ("coord"), {pattern {natural_type, x}})},
            call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &>::make (coord_invert), {X})}));

        m = m.define (binary_operand::divide, coord_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}),
            call::make (symbol::make ("coord"), {pattern {natural_type, y}}),
            call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (coord_divide), {X, Y})}));

        // arithmetic for secrets
        m = m.define (binary_operand::plus, secret_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (secret_plus), {X, Y})}));

        m = m.define (binary_operand::minus, secret_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (secret_minus), {X, Y})}));

        m = m.define (binary_operand::times, secret_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (secret_times), {X, Y})}));

        m = m.define (symbol {"invert"}, secret_type,
            {call::make (symbol::make ("secret"), {pattern {natural_type, x}})},
            call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &>::make (&secret_invert), {X})}));

        m = m.define (binary_operand::divide, secret_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}),
            call::make (symbol::make ("secret"), {pattern {natural_type, y}}),
            call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (secret_divide), {X, Y})}));

        // power
        m = m.define (binary_operand::power, natural_type, {natural_type, x}, {natural_type, y},
            call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (&natural_power), {X, Y}));

        m = m.define (symbol {"power"}, natural_type, {{natural_type, x}, {natural_type, y}},
            call::make (built_in_func<data::N,
                const data::N &, const data::N &>::make (&natural_power), {X, Y}));

        m = m.define (binary_operand::power, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_func<data::Z,
                const data::Z &, const data::N &>::make (&integer_power), {X, Y}));

        m = m.define (symbol {"power"}, integer_type, {{integer_type, x}, {integer_type, y}},
            call::make (built_in_func<data::Z,
                const data::Z &, const data::N &>::make (&integer_power), {X, Y}));

        m = m.define (binary_operand::power, scriptnum_type,
            scriptnum_pattern (x),
            {natural_type, y},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::N &>::make (&scriptnum_power), {X, Y})}));

        m = m.define (symbol {"power"}, scriptnum_type, {
            scriptnum_pattern (x),
            pattern {natural_type, y}},
            call::make (symbol::make ("scriptnum"), {call::make (built_in_func<data::bytes,
                const data::bytes &, const data::N &>::make (&scriptnum_power), {X, Y})}));

        m = m.define (binary_operand::power, coord_type,
            call::make (symbol::make ("coord"), {pattern {natural_type, x}}), {integer_type, y},
            call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &, const data::Z &>::make (&coord_power), {X, Y})}));

        m = m.define (symbol {"power"}, coord_type, {
                call::make (symbol::make ("coord"), {pattern {natural_type, x}}), {integer_type, y},
            }, call::make (symbol::make ("coord"), {call::make (built_in_func<data::N,
                const data::N &, const data::Z &>::make (&coord_power), {X, Y})}));

        m = m.define (binary_operand::power, secret_type,
            call::make (symbol::make ("secret"), {pattern {natural_type, x}}), {integer_type, y},
            call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &, const data::Z &>::make (&secret_power), {X, Y})}));

        m = m.define (symbol {"power"}, secret_type, {
                call::make (symbol::make ("secret"), {pattern {natural_type, x}}), {integer_type, y},
            }, call::make (symbol::make ("secret"), {call::make (built_in_func<data::N,
                const data::N &, const data::Z &>::make (&secret_power), {X, Y})}));

        // TODO rational types

        // now let's do some elliptic curve operations

        // valid for secret and coord.
        m = m.define (symbol ("valid"), bool_type,
            {call::make (symbol::make ("coord"), {pattern {natural_type, x}})},
            call::make (built_in_func<bool, const data::N &>::make (coord_valid), {X}));

        m = m.define (symbol ("valid"), bool_type,
            {call::make (symbol::make ("secret"), {pattern {natural_type, x}})},
            call::make (built_in_func<bool, const data::N &>::make (secret_valid), {X}));

        // define a pubkey type
        type pubkey_type {symbol::make ("pubkey")};

        m = m.define (symbol {"valid"}, bool_type, {{pubkey_type, x}},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &>::make (&pubkey_valid), {X}));

        m = m.define (binary_operand::identical, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_identical), {X, Y}));

        m = m.define (symbol {"identical"}, bool_type, {{pubkey_type, x}, {pubkey_type, y}},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_identical), {X, Y}));

        m = m.define (binary_operand::bool_unequal, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_unequal), {X, Y}));

        m = m.define (binary_operand::bool_equal, bool_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_equal), {X, Y}));

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

        m = m.define (symbol {"to_public"}, pubkey_type,
            {{bool_type, x},
                call::make (symbol::make ("secret"), {pattern {natural_type, y}})},
            call::make (built_in_func<secp256k1::pubkey,
                bool, const data::N &>::make (&secret_to_public), {X, Y}));

        m = m.define (unary_operand::negate, pubkey_type, {pubkey_type, x},
            call::make (built_in_func<secp256k1::pubkey,
                const secp256k1::pubkey &>::make (&pubkey_negate), {X}));

        m = m.define (binary_operand::plus, pubkey_type, {pubkey_type, x}, {pubkey_type, y},
            call::make (built_in_func<secp256k1::pubkey,
                const secp256k1::pubkey &, const secp256k1::pubkey &>::make (&pubkey_plus), {X, Y}));

        m = m.define (binary_operand::times, pubkey_type, {secret_type, x}, {pubkey_type, y},
            call::make (built_in_func<secp256k1::pubkey,
                const data::N, const secp256k1::pubkey &>::make (&pubkey_times), {X, Y}));

        m = m.define (binary_operand::times, pubkey_type, {pubkey_type, x}, {secret_type, y},
            call::make (built_in_func<secp256k1::pubkey,
                const secp256k1::pubkey &, const data::N &>::make (&pubkey_times), {X, Y}));

        //m = m.define (symbol {"Satoshi"}, call::make (symbol::make ("sats"), {int64_little_type}));
        m = m.define (symbol {"Pubkey"}, call::make (symbol::make ("pubkey"), {bytes_type}));
        m = m.define (symbol {"ScriptNum"}, call::make (symbol::make ("scriptnum"), {bytes_type}));

        // push
        m = m.define (symbol {"push"}, scriptnum_type, {scriptnum_type, x},
            call::make (built_in_func<data::bytes,
                const Bitcoin::integer &>::make (&push), {X}));

        m = m.define (symbol {"push"}, scriptnum_type, {string_type, x},
            call::make (built_in_func<data::bytes,
                const data::bytes &>::make (&push), {X}));

        m = m.define (symbol {"push"}, scriptnum_type, {secret_type, x},
            call::make (built_in_func<data::bytes,
                const data::uint256_little &>::make (&push), {X}));

        m = m.define (symbol {"push"}, scriptnum_type, {pubkey_type, x},
            call::make (built_in_func<data::bytes,
                const secp256k1::pubkey &>::make (&push), {X}));

        // crypto
        m = m.define (symbol {"sign"}, bytes_type,
            {call::make (symbol::make ("secret"), {pattern {natural_type, x}}), {secret_type, y}},
            call::make (built_in_func<data::bytes,
                const data::N &, const data::uint256_little &>::make (&sign), {X, Y}));

        m = m.define (symbol {"verify"}, bool_type, {{pubkey_type, x}, {bytes_type, y}, {bytes_type, z}},
            call::make (built_in_func<bool,
                const secp256k1::pubkey &, const data::bytes &, const data::bytes &>::make (verify), {X, Y, Z}));

        // hash functions
        m = m.define (symbol {"SHA1_160"}, bytes_type, {{bytes_type, x}},
            call::make (built_in_func<data::bytes, const data::bytes &>::make (SHA1_128), {X}));

        m = m.define (symbol {"SHA1_160"}, bytes_type, {{string_type, x}},
            call::make (built_in_func<data::bytes, const data::string &>::make (SHA1_128), {X}));

        m = m.define (symbol {"RIPEMD_160"}, bytes_type, {{bytes_type, x}},
            call::make (built_in_func<data::bytes, const data::bytes &>::make (RIPEMD_160), {X}));

        m = m.define (symbol {"RIPEMD_160"}, bytes_type, {{string_type, x}},
            call::make (built_in_func<data::bytes, const data::string &>::make (RIPEMD_160), {X}));

        m = m.define (symbol {"SHA2_256"}, bytes_type, {{bytes_type, x}},
            call::make (built_in_func<data::bytes, const data::bytes &>::make (SHA2_256), {X}));

        m = m.define (symbol {"SHA2_256"}, bytes_type, {{string_type, x}},
            call::make (built_in_func<data::bytes, const data::string &>::make (SHA2_256), {X}));

        m = m.define (symbol {"SHA3_256"}, bytes_type, {{bytes_type, x}},
            call::make (built_in_func<data::bytes, const data::bytes &>::make (SHA3_256), {X}));

        m = m.define (symbol {"SHA3_256"}, bytes_type, {{string_type, x}},
            call::make (built_in_func<data::bytes, const data::string &>::make (SHA3_256), {X}));

        m = m.define (symbol {"Hash160"}, bytes_type, {{bytes_type, x}},
            call::make (built_in_func<data::bytes, const data::bytes &>::make (Hash160), {X}));

        m = m.define (symbol {"Hash160"}, bytes_type, {{pubkey_type, x}},
            call::make (built_in_func<data::bytes, const secp256k1::pubkey &>::make (Hash160), {X}));

        m = m.define (symbol {"Hash160"}, bytes_type, {{string_type, x}},
            call::make (built_in_func<data::bytes, const data::string &>::make (Hash160), {X}));

        m = m.define (symbol {"Hash256"}, bytes_type, {{bytes_type, x}},
            call::make (built_in_func<data::bytes, const data::bytes &>::make (Hash256), {X}));

        m = m.define (symbol {"Hash256"}, bytes_type, {{string_type, x}},
            call::make (built_in_func<data::bytes, const data::string &>::make (Hash256), {X}));

        // base 58
        m = m.define (symbol {"base58_decode"}, integer_type, {{string_type, x}},
            call::make (built_in_func<data::N,
                const data::string &>::make (&decode_base_58), {X}));

        m = m.define (symbol {"base58_encode"}, string_type, {{integer_type, x}},
            call::make (built_in_func<data::string,
                const data::N &>::make (&encode_base_58), {X}));

        m = m.define (symbol {"base58_check_decode"},
            list::make ({uint8_type, bytes_type}),
            {pattern {string_type, x}},
            call::make (built_in_func<std::tuple<data::byte, data::bytes>,
                const data::string &>::make (&decode_base_58_check), {X}));

        m = m.define (symbol {"base58_check_encode"}, string_type,
            {list::make ({pattern {uint8_type, x}, pattern {bytes_type, y}})},
            call::make (built_in_func<data::string,
                const data::byte &, const data::bytes &>::make (&encode_base_58_check), {X, Y}));

        m = m.define (symbol {"base58"}, dstruct::make ({
            {symbol {"decode"}, expression {"base58_decode"}},
            {symbol {"encode"}, expression {"base58_encode"}},
            {symbol {"check"}, dstruct::make ({
                {symbol {"decode"}, expression {"base58_check_decode"}},
                {symbol {"encode"}, expression {"base58_check_encode"}}
            })}
        }));

        // net
        type net_type {symbol::make ("net")};

        m = m.define (binary_operand::dot, net_type,
            symbol::make ("net"),
            symbol::make ("Main"),
            net::make (Bitcoin::net::Main));

        m = m.define (binary_operand::dot, net_type,
            symbol::make ("net"),
            symbol::make ("Test"),
            net::make (Bitcoin::net::Test));

        m = m.define (binary_operand::dot, net_type,
            symbol::make ("net"),
            symbol::make ("invalid"),
            net::make (Bitcoin::net::Invalid));

        m = m.define (symbol {"address_encode"}, string_type,
            {list::make ({pattern {bytes_type, y}, pattern {net_type, x}})},
            call::make (built_in_func<data::string, const data::bytes &, Bitcoin::net>::make (address_encode), {Y, X}));

        m = m.define (symbol {"address_encode"}, string_type,
            {list::make ({pattern {bytes_type, y}})},
            call::make (built_in_func<data::string, const data::bytes &, Bitcoin::net>::make (address_encode),
                {Y, net::make (Bitcoin::net::Main)}));

        m = m.define (symbol {"address_decode"},
            list::make ({bytes_type, net_type}),
            {{string_type, x}},
            call::make (built_in_func<data::tuple<data::bytes, Bitcoin::net>, const data::string &>::make (address_decode), {X}));

        m = m.define (symbol {"WIF_encode"}, string_type,
            {list::make ({pattern {bytes_type, x}, pattern {net_type, y}, pattern {bool_type, z}})},
            call::make (built_in_func<data::string, const data::N &, Bitcoin::net, bool>::make (WIF_encode), {X, Y, Z}));

        m = m.define (symbol {"WIF_encode"}, string_type,
            {list::make ({pattern {bytes_type, x}, pattern {net_type, y}})},
            call::make (built_in_func<data::string, const data::N &, Bitcoin::net, bool>::make (WIF_encode),
                {X, Y, leaf<bool>::make (true)}));

        m = m.define (symbol {"WIF_encode"}, string_type,
            {list::make ({pattern {bytes_type, x}})},
            call::make (built_in_func<data::string, const data::N &, Bitcoin::net, bool>::make (WIF_encode),
                {X, net::make (Bitcoin::net::Main), leaf<bool>::make (true)}));

        m = m.define (symbol {"WIF_decode"},
            list::make ({bytes_type, net_type, bool_type}),
            {{string_type, x}},
            call::make (built_in_func<data::tuple<data::N, Bitcoin::net, bool>, const data::string &>::make (WIF_decode),
                {Y, net::make (Bitcoin::net::Main)}));

        m = m.define (binary_operand::dot,
            symbol::make ("address"),
            symbol::make ("decode"),
            symbol::make ("address_decode"));

        m = m.define (binary_operand::dot,
            symbol::make ("address"),
            symbol::make ("encode"),
            symbol::make ("address_encode"));

        m = m.define (binary_operand::dot,
            symbol::make ("WIF"),
            symbol::make ("decode"),
            symbol::make ("WIF_decode"));

        m = m.define (binary_operand::dot,
            symbol::make ("WIF"),
            symbol::make ("encode"),
            symbol::make ("WIF_encode"));

        type address_type {call::make (symbol::make ("address"), {string_type})};

        // addresses from pubkeys and wifs.
        m = m.define (symbol {"address"}, address_type,
            {{net_type, x}, {pubkey_type, y}},
            call::make (built_in_func<data::string, const secp256k1::pubkey &, Bitcoin::net>::make (address_from_pubkey), {Y, X}));

        m = m.define (symbol {"address"}, address_type,
            {{bool_type, x}, {net_type, y}, call::make (symbol {"secret"}, {pattern {natural_type, z}})},
            call::make (built_in_func<data::string, const data::N &, Bitcoin::net, bool>::make (address_from_secret), {Z, Y, X}));

        m = m.define (symbol {"address"}, address_type,
            {call::make (symbol::make ("WIF"), {pattern {string_type, x}})},
            call::make (built_in_func<data::string, const data::string &>::make (address_from_WIF), {X}));

        // WIF sign
        m = m.define (symbol {"sign"}, scriptnum_type, {{secret_type, x}, {secret_type, y}},
            call::make (built_in_func<data::bytes,
                const data::string &, const data::uint256_little &>::make (&sign_with_WIF), {X, Y}));
/*
        expression A = symbol::make ("a");
        expression B = symbol::make ("b");
        expression C = symbol::make ("c");

        Symbol a = dynamic_cast<Symbol> (*A.get ());
        Symbol b = dynamic_cast<Symbol> (*B.get ());
        Symbol c = dynamic_cast<Symbol> (*C.get ());

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({pattern {pubkey_type, x}, pattern {bytes_type, y}, pattern {net_type, z},
                pattern {bytes_type, a}, pattern {uint32_type, b}, pattern {uint32_type, c}})},
            call::make (built_in_func<data::string, const secp256k1::pubkey &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_pubkey),
                {X, Y, Z, A, B, C}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({call::make (symbol::make ("secret"), {pattern {natural_type, x}}), pattern {bytes_type, y}, pattern {net_type, z},
                pattern {uint8_type, a}, pattern {uint32_type, b}, pattern {uint32_type, c}})},
            call::make (built_in_func<data::string, const data::N &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_secret),
                {X, Y, Z, A, B, C}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({pattern {pubkey_type, x}, pattern {bytes_type, y}, pattern {net_type, z},
                pattern {bytes_type, a}, pattern {uint32_type, b}})},
            call::make (built_in_func<data::string, const secp256k1::pubkey &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_pubkey),
                {X, Y, Z, A, B, uint32::make (0)}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({call::make (symbol::make ("secret"), {pattern {natural_type, x}}), pattern {bytes_type, y}, pattern {net_type, z},
                pattern {uint8_type, a}, pattern {uint32_type, b}})},
            call::make (built_in_func<data::string, const data::N &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_secret),
                {X, Y, Z, A, B, uint32::make (0)}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({pattern {pubkey_type, x}, pattern {bytes_type, y}, pattern {net_type, z},
                pattern {bytes_type, a}})},
            call::make (built_in_func<data::string, const secp256k1::pubkey &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_pubkey),
                {X, Y, Z, A, uint32::make (0), uint32::make (0)}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({call::make (symbol::make ("secret"), {pattern {natural_type, x}}), pattern {bytes_type, y}, pattern {net_type, z},
                pattern {uint8_type, a}})},
            call::make (built_in_func<data::string, const data::N &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_secret),
                {X, Y, Z, A, uint32::make (0), uint32::make (0)}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({pattern {pubkey_type, x}, pattern {bytes_type, y}, pattern {net_type, z}})},
            call::make (built_in_func<data::string, const secp256k1::pubkey &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_pubkey),
                {X, Y, Z, uint8::make (0), uint32::make (0), uint32::make (0)}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({call::make (symbol::make ("secret"), {pattern {natural_type, x}}), pattern {bytes_type, y}, pattern {net_type, z}})},
            call::make (built_in_func<data::string, const data::N &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_secret),
                {X, Y, Z, uint8::make (0), uint32::make (0), uint32::make (0)}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({pattern {pubkey_type, x}, pattern {bytes_type, y}})},
            call::make (built_in_func<data::string, const secp256k1::pubkey &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_pubkey),
                {X, Y, leaf<Bitcoin::net>::make (Bitcoin::net::Main),
                    uint8::make (0), uint32::make (0), uint32::make (0)}));

        m = m.define (symbol {"HD_encode"}, string_type,
            {list::make ({call::make (symbol::make ("secret"), {pattern {natural_type, x}}), pattern {bytes_type, y}})},
            call::make (built_in_func<data::string, const data::N &,
                const data::bytes &, Bitcoin::net, data::byte, data::uint32, data::uint32>::make (encode_HD_secret),
                {X, Y, leaf<Bitcoin::net>::make (Bitcoin::net::Main),
                    uint8::make (0), uint32::make (0), uint32::make (0)}));*/
/*
        type xpub_type {call::make (binop::make (binary_operand::dot, symbol::make ("HD"), symbol::make ("pubkey")), {string_type})};
        type xprv_type {call::make (binop::make (binary_operand::dot, symbol::make ("HD"), symbol::make ("secret")), {string_type})};

        // HD key
        m = m.define (symbol {"secret"}, secret_type, {call::make (symbol::make ("HD_secret"), {pattern {string_type, x}})},
            call::make (symbol::make ("secret"),
                {call::make (built_in_func<data::N, const data::string &>::make (hd_get_secret), {X})}));

        m = m.define (symbol {"pubkey"}, pubkey_type, {call::make (symbol::make ("HD_pubkey"), {pattern {string_type, x}})},
            call::make (symbol::make ("pubkey"),
                {call::make (built_in_func<secp256k1::pubkey, const data::string &>::make (hd_get_pubkey), {X})}));*/


/*
        // HD derive
        m = m.define (binary_operand::divide, xpub_type,
            call::make (symbol::make ("HD_pubkey"), {pattern {string_type, x}}),
            pattern {natural_type, y},
            call::make (symbol::make ("HD_pubkey"),
                {call::make (built_in_func<data::string, const data::string &, const data::N &>::make (hd_pubkey_derive), {x, y})}));

        m = m.define (binary_operand::divide, xprv_type,
            call::make (symbol::make ("HD_secret"), {pattern {string_type, x}}),
            pattern {natural_type, y},
            call::make (symbol::make ("HD_secret"),
                {call::make (built_in_func<data::string, const data::string &, const data::N &>::make (hd_derive), {x, y})}));

        m = m.define (binary_operand::divide, xprv_type,
            call::make (symbol::make ("HD_secret"), {pattern {string_type, x}}),
            unop::make (unary_operand::harden, {pattern {natural_type, y}}),
            call::make (symbol::make ("HD_secret"),
                {call::make (built_in_func<data::string, const data::string &, const data::N &>::make (hd_derive_hardened), {x, y})}));*/

        // HD sign

        // HD verify

        // HD address

/*

        type sats_type {symbol::make ("satoshi")};

        m = m.define (symbol {"sighash_all"}, byte::make (data::byte (1)));
        m = m.define (symbol {"sighash_none"}, byte::make (data::byte (2)));
        m = m.define (symbol {"sighash_single"}, byte::make (data::byte (3)));
        m = m.define (symbol {"sighash_anyone_can_pay"}, byte::make (data::byte (0x80)));
        m = m.define (symbol {"sighash_forkid"}, byte::make (data::byte (0x40)));*/

        return m;
    }

    data::bytes push (const data::uint256_little &x) {
        return Bitcoin::compile (Bitcoin::push_data (data::Z (x)));
    }

    data::bytes push (const Bitcoin::integer &x) {
        return Bitcoin::compile (Bitcoin::push_data (x));
    }

    data::bytes push (const data::bytes &x) {
        return Bitcoin::compile (Bitcoin::push_data (data::bytes (x)));
    }

    data::bytes push (const secp256k1::pubkey &x) {
        return Bitcoin::compile (Bitcoin::push_data (data::bytes (x)));
    }

}

