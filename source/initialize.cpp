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
        std::cout << "INITIALIZING MACHINE" << std::endl;
        machine m {};

        type nil {expression {}};

        m = m.define (symbol {"Nil"}, nil, nil);

        // the fundamental types.
        type secret_type {symbol::make ("private")};
        type pubkey_type {symbol::make ("public")};
        type integer_type {symbol::make ("scriptnum")};
        type string_type {symbol::make ("string")};
        type sats_type {symbol::make ("satoshi")};
        type &bool_type = integer_type;

        // number operations

        // boolean operations
        m = m.define (symbol {"False"}, bool_type, scriptnum::make (Bitcoin::integer {0}));
        m = m.define (symbol {"True"}, bool_type, scriptnum::make (Bitcoin::integer {1}));

        m = m.define (unary_operand::bool_not, bool_type, bool_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &>::make (&scriptnum_bool_not));

        m = m.define (binary_operand::bool_and, bool_type, bool_type, bool_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_and));

        m = m.define (binary_operand::bool_or, bool_type, bool_type, bool_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bool_or));

        // bit operations
        m = m.declare (unary_operand::tilda, integer_type, integer_type);

        m = m.define (binary_operand::bit_and, integer_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_and));

        m = m.define (binary_operand::bit_or, integer_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_bit_or));

        m = m.declare (binary_operand::bit_xor, integer_type, integer_type, integer_type);

        m = m.define (binary_operand::identical, integer_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_identical));

        // comparisons
        m = m.define (binary_operand::equal, bool_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_equal));

        m = m.define (binary_operand::unequal, bool_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_not_equal));

        m = m.define (binary_operand::greater_equal, bool_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_greater_equal));

        m = m.define (binary_operand::less_equal, bool_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_less_equal));

        m = m.define (binary_operand::greater, bool_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_greater));

        m = m.define (binary_operand::less, bool_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_less));

        // comparisons
        m = m.define (binary_operand::equal, bool_type, secret_type, secret_type,
            built_in_function<Bitcoin::integer, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_equal));

        m = m.define (binary_operand::unequal, bool_type, secret_type, secret_type,
            built_in_function<Bitcoin::integer, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_not_equal));

        m = m.define (binary_operand::greater_equal, bool_type, secret_type, secret_type,
            built_in_function<Bitcoin::integer, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_greater_equal));

        m = m.define (binary_operand::less_equal, bool_type, secret_type, secret_type,
            built_in_function<Bitcoin::integer, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_less_equal));

        m = m.define (binary_operand::greater, bool_type, secret_type, secret_type,
            built_in_function<Bitcoin::integer, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_greater));

        m = m.define (binary_operand::less, bool_type, secret_type, secret_type,
            built_in_function<Bitcoin::integer, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_less));

        // arithmetic
        m = m.define (unary_operand::negate, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &>::make (&scriptnum_negate));

        m = m.define (binary_operand::plus, integer_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_plus));

        m = m.define (binary_operand::minus, integer_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_minus));

        m = m.define (binary_operand::times, integer_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_times));

        m = m.define (binary_operand::divide, integer_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_divide));

        m = m.define (binary_operand::mod, integer_type, integer_type, integer_type,
            built_in_function<Bitcoin::integer, const Bitcoin::integer &, const Bitcoin::integer &>::make (&scriptnum_mod));

        // arithmetic
        m = m.define (unary_operand::negate, secret_type, secret_type,
            built_in_function<secp256k1::secret, const secp256k1::secret &>::make (&secret_negate));

        m = m.define (binary_operand::plus, secret_type, secret_type, secret_type,
            built_in_function<secp256k1::secret, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus));

        m = m.define (binary_operand::minus, secret_type, secret_type, secret_type,
            built_in_function<secp256k1::secret, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus));

        m = m.define (binary_operand::times, secret_type, secret_type, secret_type,
            built_in_function<secp256k1::secret, const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus));

        m = m.declare (symbol {"Inverse"}, secret_type, {secret_type});

        m = m.declare (binary_operand::divide, secret_type, secret_type, secret_type);

        // power
        m = m.declare (binary_operand::power, secret_type, secret_type, secret_type);

        m = m.declare (symbol {"Power"}, secret_type, {secret_type, secret_type});

        m = m.declare (binary_operand::power, integer_type, integer_type, secret_type);

        m = m.declare (symbol {"Power"}, integer_type, {secret_type, secret_type});

        // pubkey and secret operations
        m = m.declare (binary_operand::equal, bool_type, pubkey_type, pubkey_type);
        m = m.declare (binary_operand::unequal, bool_type, pubkey_type, pubkey_type);

        m = m.declare (binary_operand::plus, pubkey_type, pubkey_type, pubkey_type);
        m = m.declare (binary_operand::times, pubkey_type, secret_type, pubkey_type);
        m = m.declare (binary_operand::times, pubkey_type, pubkey_type, secret_type);

        m = m.declare (symbol {"Valid"}, integer_type, {secret_type});
        m = m.declare (symbol {"Valid"}, integer_type, {pubkey_type});

        m = m.declare (symbol {"to_public"}, pubkey_type, {secret_type});

        m = m.declare (symbol {"Sign"}, integer_type, {secret_type, integer_type});
        m = m.declare (symbol {"Sign"}, integer_type, {secret_type, secret_type});

        m = m.declare (symbol {"Verify"}, bool_type, {pubkey_type, integer_type, integer_type});
        m = m.declare (symbol {"Verify"}, bool_type, {pubkey_type, secret_type, integer_type});

        // push operations
        m = m.declare (symbol {"Push"}, integer_type, {secret_type});
        m = m.declare (symbol {"Push"}, integer_type, {pubkey_type});
        m = m.declare (symbol {"Push"}, integer_type, {integer_type});
        m = m.declare (symbol {"Push"}, integer_type, {string_type});

        // string operations
        m = m.define (binary_operand::equal, bool_type, string_type, string_type,
            built_in_function<Bitcoin::integer, const data::string &, const data::string &>::make (&string_equal));

        m = m.define (binary_operand::unequal, bool_type, string_type, string_type,
            built_in_function<Bitcoin::integer, const data::string &, const data::string &>::make (&string_unequal));

        m = m.define (binary_operand::identical, bool_type, string_type, string_type,
            built_in_function<Bitcoin::integer, const data::string &, const data::string &>::make (&string_identical));

        m = m.declare (binary_operand::cat, integer_type, integer_type, integer_type);

        m = m.declare (binary_operand::cat, string_type, string_type, string_type);

        // bit shifts
        m = m.declare (symbol {"RightShift"}, integer_type, {integer_type});
        m = m.declare (symbol {"LeftShift"}, integer_type, {integer_type});

        m = m.declare (symbol {"RightShift"}, string_type, {integer_type});
        m = m.declare (symbol {"LeftShift"}, string_type, {integer_type});

        m = m.declare (symbol {"RightShift"}, integer_type, {secret_type});
        m = m.declare (symbol {"LeftShift"}, integer_type, {secret_type});

        m = m.declare (symbol {"RightShift"}, string_type, {secret_type});
        m = m.declare (symbol {"LeftShift"}, string_type, {secret_type});

        // size operations
        m = m.declare (symbol {"Size"}, integer_type, {integer_type});
        m = m.declare (symbol {"MinimalSize"}, integer_type, {integer_type});
        m = m.declare (symbol {"Resize"}, integer_type, {integer_type});
        m = m.declare (symbol {"Minimal"}, integer_type, {integer_type});
        m = m.declare (symbol {"MinimalQ"}, bool_type, {integer_type});

        // base 58
        m = m.declare (symbol {"ReadBase58"}, secret_type, {string_type});
        m = m.declare (symbol {"WriteBase58"}, string_type, {secret_type});

        // base 58 check
        m = m.declare (symbol {"ReadBase58Check"}, integer_type, {string_type});
        m = m.declare (symbol {"WriteBase58Check"}, string_type, {integer_type});

        // hash operations
        m = m.declare (symbol {"SHA"}, integer_type, {secret_type, secret_type, integer_type});
        m = m.declare (symbol {"RIPEMD"}, integer_type, {secret_type, integer_type});
        m = m.declare (symbol {"Hash160"}, integer_type, {integer_type});
        m = m.declare (symbol {"Hash256"}, integer_type, {integer_type});

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

