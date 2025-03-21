#include <machine.hpp>
#include <value.hpp>

namespace Diophant {

    Bitcoin::integer scriptnum_bool_not (const Bitcoin::integer &x);

    Bitcoin::integer scriptnum_bool_and (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bool_or (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer scriptnum_bit_not (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_bit_and (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bit_xor (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_bit_or (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_identical (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer scriptnum_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_not_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_greater_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_less_equal (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_greater (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_less (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer scriptnum_negate (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_plus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_minus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_times (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_divide (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_mod (const Bitcoin::integer &x, const Bitcoin::integer &y);

    Bitcoin::integer secret_identical (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_equal (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_not_equal (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_greater_equal (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_less_equal (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_greater (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_less (const secp256k1::secret &x, const secp256k1::secret &y);

    secp256k1::secret secret_negate (const secp256k1::secret &x);
    secp256k1::secret secret_plus (const secp256k1::secret &x, const secp256k1::secret &y);
    secp256k1::secret secret_minus (const secp256k1::secret &x, const secp256k1::secret &y);
    secp256k1::secret secret_times (const secp256k1::secret &x, const secp256k1::secret &y);
    secp256k1::secret secret_inverse (const secp256k1::secret &x);
    secp256k1::secret secret_divide (const secp256k1::secret &x, const secp256k1::secret &y);

    Bitcoin::integer string_equal (const data::string &x, const data::string &y);
    Bitcoin::integer string_identical (const data::string &x, const data::string &y);
    Bitcoin::integer string_unequal (const data::string &x, const data::string &y);

    data::string string_cat (const data::string &x, const data::string &y);
    data::string string_split (const data::string &x, const Bitcoin::integer &y);
    data::string string_split (const data::string &x, const secp256k1::secret &y);
    data::string string_left (const data::string &x, const Bitcoin::integer &y);
    data::string string_left (const data::string &x, const secp256k1::secret &y);
    data::string string_right (const data::string &x, const Bitcoin::integer &y);
    data::string string_right (const data::string &x, const secp256k1::secret &y);

    data::string string_shift_left (const data::string &x, const Bitcoin::integer &y);
    data::string string_shift_left (const data::string &x, const secp256k1::secret &y);
    data::string string_shift_right (const data::string &x, const Bitcoin::integer &y);
    data::string string_shift_right (const data::string &x, const secp256k1::secret &y);

    Bitcoin::integer scriptnum_cat (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_split (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_split (const Bitcoin::integer &x, const secp256k1::secret &y);
    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const secp256k1::secret &y);
    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const secp256k1::secret &y);

    Bitcoin::integer scriptnum_shift_left (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_shift_left (const Bitcoin::integer &x, const secp256k1::secret &y);
    Bitcoin::integer scriptnum_shift_right (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_shift_right (const Bitcoin::integer &x, const secp256k1::secret &y);

    secp256k1::secret secret_power (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const secp256k1::secret &y);

    Bitcoin::integer secret_valid (const secp256k1::secret &x);
    Bitcoin::integer pubkey_valid (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const secp256k1::secret &y);
    secp256k1::pubkey pubkey_times (const secp256k1::secret &x, const secp256k1::pubkey &y);

    Bitcoin::integer push (const secp256k1::secret &x);
    Bitcoin::integer push (const Bitcoin::integer &x);
    Bitcoin::integer push (const data::string &x);
    Bitcoin::integer push (const secp256k1::pubkey &x);

    machine initialize () {

        machine m {};

        type nil {expression {}};

        m = m.define (symbol {"nil"}, nil, nil);

        // the fundamental types.
        type secret_type {symbol::make ("private")};
        type pubkey_type {symbol::make ("public")};
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

        // number operations

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

        // bit operations
        m = m.declare (unary_operand::tilda, integer_type, {integer_type, x});
        m = m.declare (symbol {"BitNot"}, integer_type, {{integer_type, x}});

        m = m.define (binary_operand::bit_and, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_and), {X, Y}));

        m = m.define (binary_operand::bit_or, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_or), {X, Y}));

        m = m.declare (binary_operand::bit_xor, integer_type, {integer_type, x}, {integer_type, y});

        m = m.define (binary_operand::identical, integer_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_identical), {X, Y}));

        // comparisons
        m = m.define (binary_operand::equal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_equal), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, {integer_type, x}, {integer_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_not_equal), {X, Y}));

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
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_equal), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_not_equal), {X, Y}));

        m = m.define (binary_operand::greater_equal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_greater_equal), {X, Y}));

        m = m.define (binary_operand::less_equal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_less_equal), {X, Y}));

        m = m.define (binary_operand::greater, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_greater), {X, Y}));

        m = m.define (binary_operand::less, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_less), {X, Y}));

        // arithmetic
        m = m.define (unary_operand::negate, integer_type, {integer_type, x},
            call::make (built_in_function<Bitcoin::integer,
                const Bitcoin::integer &>::make (&scriptnum_negate), {X, Y}));

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
            call::make (built_in_function<secp256k1::secret,
                const secp256k1::secret &>::make (&secret_negate), {X, Y}));

        m = m.define (binary_operand::plus, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<secp256k1::secret,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus), {X, Y}));

        m = m.define (binary_operand::minus, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<secp256k1::secret,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus), {X, Y}));

        m = m.define (binary_operand::times, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<secp256k1::secret,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus), {X, Y}));

        m = m.declare (symbol {"Inverse"}, secret_type, {secret_type, x});

        m = m.declare (binary_operand::divide, secret_type, {secret_type, x}, {secret_type, y});

        // power
        m = m.declare (binary_operand::power, secret_type, {secret_type, x}, {secret_type, y});

        m = m.declare (symbol {"Power"}, secret_type, {{secret_type, x}, {secret_type, y}});

        m = m.declare (binary_operand::power, integer_type, integer_type, secret_type);

        m = m.declare (symbol {"Power"}, integer_type, {{secret_type, x}, {secret_type, y}});

        // pubkey and secret operations
        m = m.declare (binary_operand::equal, bool_type, {pubkey_type, x}, {pubkey_type, y});
        m = m.declare (binary_operand::unequal, bool_type, {pubkey_type, x}, {pubkey_type, y});

        m = m.declare (binary_operand::plus, pubkey_type, {pubkey_type, x}, {pubkey_type, y});
        m = m.declare (binary_operand::times, pubkey_type, {pubkey_type, x}, {pubkey_type, y});
        m = m.declare (binary_operand::times, pubkey_type, {pubkey_type, x}, {pubkey_type, y});

        m = m.declare (symbol {"Valid"}, integer_type, {{secret_type, x}});
        m = m.declare (symbol {"Valid"}, integer_type, {{pubkey_type, x}});

        m = m.declare (symbol {"to_public"}, pubkey_type, {{secret_type, x}});

        m = m.declare (symbol {"Sign"}, integer_type, {secret_type, integer_type});
        m = m.declare (symbol {"Sign"}, integer_type, {secret_type, secret_type});

        m = m.declare (symbol {"Verify"}, bool_type, {pubkey_type, integer_type, integer_type});
        m = m.declare (symbol {"Verify"}, bool_type, {pubkey_type, secret_type, integer_type});

        // push operations
        m = m.declare (symbol {"Push"}, integer_type, {{secret_type, x}});
        m = m.declare (symbol {"Push"}, integer_type, {{pubkey_type, x}});
        m = m.declare (symbol {"Push"}, integer_type, {{integer_type, x}});
        m = m.declare (symbol {"Push"}, integer_type, {{string_type, x}});

        // string operations
        m = m.define (binary_operand::equal, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const data::string &, const data::string &>::make (string_equal), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const data::string &, const data::string &>::make (&string_unequal), {X, Y}));

        m = m.define (binary_operand::identical, bool_type, {string_type, x}, {string_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const data::string &, const data::string &>::make (&string_identical), {X, Y}));

        m = m.declare (binary_operand::cat, integer_type, integer_type, integer_type);

        m = m.declare (binary_operand::cat, string_type, {string_type, x}, {string_type, y});

        // bit shifts
        m = m.declare (symbol {"RightShift"}, integer_type, {{integer_type, x}});
        m = m.declare (symbol {"LeftShift"}, integer_type, {{integer_type, x}});

        m = m.declare (symbol {"RightShift"}, string_type, {{integer_type, x}});
        m = m.declare (symbol {"LeftShift"}, string_type, {{integer_type, x}});

        m = m.declare (symbol {"RightShift"}, integer_type, {{secret_type, x}});
        m = m.declare (symbol {"LeftShift"}, integer_type, {{secret_type, x}});

        m = m.declare (symbol {"RightShift"}, string_type, {{secret_type, x}});
        m = m.declare (symbol {"LeftShift"}, string_type, {{secret_type, x}});

        // size operations
        m = m.declare (symbol {"Size"}, integer_type, {{integer_type, x}});
        m = m.declare (symbol {"MinimalSize"}, integer_type, {{integer_type, x}});
        m = m.declare (symbol {"Resize"}, integer_type, {{integer_type, x}});
        m = m.declare (symbol {"Minimal"}, integer_type, {{integer_type, x}});
        m = m.declare (symbol {"MinimalQ"}, bool_type, {{integer_type, x}});

        // base 58
        m = m.declare (symbol {"ReadBase58"}, secret_type, {{string_type, x}});
        m = m.declare (symbol {"WriteBase58"}, string_type, {{secret_type, x}});

        // base 58 check
        m = m.declare (symbol {"ReadBase58Check"}, integer_type, {{string_type, x}});
        m = m.declare (symbol {"WriteBase58Check"}, string_type, {{integer_type, x}});

        // hash operations
        m = m.declare (symbol {"SHA"}, integer_type, {{secret_type, x}, {secret_type, y}, {integer_type, z}});
        m = m.declare (symbol {"RIPEMD"}, integer_type, {{secret_type, x}, {integer_type, y}});
        m = m.declare (symbol {"Hash160"}, integer_type, {{integer_type, x}});
        m = m.declare (symbol {"Hash256"}, integer_type, {{integer_type, x}});

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
/*
    Bitcoin::integer scriptnum_bit_not (const Bitcoin::integer &x) {
        return ~x;
    }*/

    Bitcoin::integer scriptnum_bit_and (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x & y;
    }
/*
    Bitcoin::integer scriptnum_bit_xor (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x ^ y;
    }*/

    Bitcoin::integer scriptnum_bit_or (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x | y;
    }

    Bitcoin::integer scriptnum_identical (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {data::identical (x, y)};
    }

    Bitcoin::integer string_equal (const data::string &x, const data::string &y) {
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer string_identical (const data::string &x, const data::string &y) {
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer string_unequal (const data::string &x, const data::string &y) {
        return Bitcoin::integer {x != y};
    }

    Bitcoin::integer scriptnum_equal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x == y;
    }

    Bitcoin::integer scriptnum_not_equal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
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

    Bitcoin::integer secret_identical (const secp256k1::secret &x, const secp256k1::secret &y) {
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer secret_equal (const secp256k1::secret &x, const secp256k1::secret &y) {
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer secret_not_equal (const secp256k1::secret &x, const secp256k1::secret &y) {
        return Bitcoin::integer {x != y};
    }

    Bitcoin::integer secret_greater_equal (const secp256k1::secret &x, const secp256k1::secret &y) {
        return Bitcoin::integer {x.Value <= y.Value};
    }

    Bitcoin::integer secret_less_equal (const secp256k1::secret &x, const secp256k1::secret &y) {
        return Bitcoin::integer {x.Value >= y.Value};
    }

    Bitcoin::integer secret_greater (const secp256k1::secret &x, const secp256k1::secret &y) {
        return Bitcoin::integer {x.Value < y.Value};
    }

    Bitcoin::integer secret_less (const secp256k1::secret &x, const secp256k1::secret &y) {
        return Bitcoin::integer {x.Value > y.Value};
    }

    secp256k1::secret secret_negate (const secp256k1::secret &x) {
        return -x;
    }

    secp256k1::secret secret_plus (const secp256k1::secret &x, const secp256k1::secret &y) {
        return x + y;
    }

    secp256k1::secret secret_minus (const secp256k1::secret &x, const secp256k1::secret &y) {
        return x + -y;
    }

    secp256k1::secret secret_times (const secp256k1::secret &x, const secp256k1::secret &y) {
        return x * y;
    }

    /*
    secp256k1::secret secret_divide (const secp256k1::secret &x, const secp256k1::secret &y);
    secp256k1::secret secret_mod (const secp256k1::secret &x, const secp256k1::secret &y);

    secp256k1::secret secret_power (const secp256k1::secret &x, const secp256k1::secret &y) {
        return data::math::pow_mod<data::uint512> {}
            (data::uint512 (secp256k1::secret::order ()), data::uint512 (x.Value), data::uint512 (y.Value));
    }

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const secp256k1::secret &y) {

    }*/

}

