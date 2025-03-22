#include <machine.hpp>
#include <value.hpp>

namespace Diophant {

    // string operations
    data::string string_cat (const data::string &x, const data::string &y);
    data::string string_left (const data::string &x, const Bitcoin::integer &y);
    data::string string_left (const data::string &x, const secp256k1::secret &y);
    data::string string_right (const data::string &x, const Bitcoin::integer &y);
    data::string string_right (const data::string &x, const secp256k1::secret &y);

    Bitcoin::integer scriptnum_cat (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const secp256k1::secret &y);
    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const secp256k1::secret &y);

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const secp256k1::secret &y);
    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const secp256k1::secret &y);

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

    Bitcoin::integer secret_equal (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_unequal (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_greater_equal (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_less_equal (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_greater (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer secret_less (const secp256k1::secret &x, const secp256k1::secret &y);

    Bitcoin::integer pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    Bitcoin::integer pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    Bitcoin::integer pubkey_unqual (const secp256k1::pubkey &x, const secp256k1::pubkey &y);

    // size operations
    Bitcoin::integer scriptnum_size (const Bitcoin::integer &x);
    data::string string_size (const data::string &x);

    Bitcoin::integer scriptnum_minimal_size (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_minimal (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_is_minimal (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const secp256k1::secret &y);

    // arithmetic
    Bitcoin::integer scriptnum_negate (const Bitcoin::integer &x);
    Bitcoin::integer scriptnum_plus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_minus (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_times (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_divide (const Bitcoin::integer &x, const Bitcoin::integer &y);
    Bitcoin::integer scriptnum_mod (const Bitcoin::integer &x, const Bitcoin::integer &y);

    secp256k1::secret secret_negate (const secp256k1::secret &x);
    secp256k1::secret secret_plus (const secp256k1::secret &x, const secp256k1::secret &y);
    secp256k1::secret secret_minus (const secp256k1::secret &x, const secp256k1::secret &y);
    secp256k1::secret secret_times (const secp256k1::secret &x, const secp256k1::secret &y);

    // base 58
    secp256k1::secret read_base_58 (const data::string &x);
    data::string write_base_58 (const secp256k1::secret &x);

    Bitcoin::integer read_base_58_check (const data::string &x);
    data::string write_base_58_check (const Bitcoin::integer &x);

    // advanced math
    secp256k1::secret secret_inverse (const secp256k1::secret &x);
    secp256k1::secret secret_divide (const secp256k1::secret &x, const secp256k1::secret &y);

    secp256k1::secret secret_power (const secp256k1::secret &x, const secp256k1::secret &y);
    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const secp256k1::secret &y);

    // elliptic curve
    Bitcoin::integer secret_valid (const secp256k1::secret &x);
    Bitcoin::integer pubkey_valid (const secp256k1::pubkey &x);

    Bitcoin::integer pubkey_compressed (const secp256k1::pubkey &x);
    Bitcoin::integer pubkey_uncompressed (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_compress (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_decompress (const secp256k1::pubkey &x);

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x);
    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y);
    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const secp256k1::secret &y);
    secp256k1::pubkey pubkey_times (const secp256k1::secret &x, const secp256k1::pubkey &y);

    // script
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

        // string operations
        m = m.declare (binary_operand::cat, integer_type, {integer_type, x}, {integer_type, x});

        m = m.declare (binary_operand::cat, string_type, {string_type, x}, {string_type, y});

        m = m.declare (symbol {"Left"}, integer_type, {{integer_type, x}, {integer_type, x}});

        m = m.declare (symbol {"Left"}, string_type, {{string_type, x}, {string_type, y}});

        m = m.declare (symbol {"Right"}, integer_type, {{integer_type, x}, {integer_type, x}});

        m = m.declare (symbol {"Right"}, string_type, {{string_type, x}, {string_type, y}});

        // bit shifts
        m = m.declare (symbol {"RightShift"}, integer_type, {{integer_type, x}, {integer_type, y}});
        m = m.declare (symbol {"LeftShift"}, integer_type, {{integer_type, x}, {integer_type, y}});

        m = m.declare (symbol {"RightShift"}, integer_type, {{integer_type, x}, {secret_type, y}});
        m = m.declare (symbol {"LeftShift"}, integer_type, {{integer_type, x}, {secret_type, y}});

        m = m.declare (symbol {"RightShift"}, string_type, {{string_type, x}, {integer_type, y}});
        m = m.declare (symbol {"LeftShift"}, string_type, {{string_type, x}, {integer_type, y}});

        m = m.declare (symbol {"RightShift"}, string_type, {{string_type, x}, {secret_type, y}});
        m = m.declare (symbol {"LeftShift"}, string_type, {{string_type, x}, {secret_type, y}});

        // bit operations
        m = m.declare (unary_operand::tilda, integer_type, {integer_type, x});
        m = m.declare (symbol {"BitNot"}, integer_type, {{integer_type, x}});

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

        // push
        m = m.declare (symbol {"Push"}, integer_type, {integer_type, x});
        m = m.declare (symbol {"Push"}, integer_type, {string_type, x});
        m = m.declare (symbol {"Push"}, integer_type, {secret_type, x});
        m = m.declare (symbol {"Push"}, integer_type, {pubkey_type, x});

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
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_equal), {X, Y}));

        m = m.define (symbol {"Identical"}, bool_type, {{secret_type, x}, {secret_type, y}},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_equal), {X, Y}));

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
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_equal), {X, Y}));

        m = m.define (binary_operand::unequal, bool_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<Bitcoin::integer,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_unequal), {X, Y}));

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
            call::make (built_in_function<secp256k1::secret,
                const secp256k1::secret &>::make (&secret_negate), {X}));

        m = m.define (binary_operand::plus, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<secp256k1::secret,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus), {X, Y}));

        m = m.define (binary_operand::minus, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<secp256k1::secret,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus), {X, Y}));

        m = m.define (binary_operand::times, secret_type, {secret_type, x}, {secret_type, y},
            call::make (built_in_function<secp256k1::secret,
                const secp256k1::secret &, const secp256k1::secret &>::make (&secret_plus), {X, Y}));

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

        // elliptic curve operations
        m = m.declare (binary_operand::equal, bool_type, {pubkey_type, x}, {pubkey_type, y});
        m = m.declare (binary_operand::unequal, bool_type, {pubkey_type, x}, {pubkey_type, y});

        m = m.declare (symbol {"Valid"}, integer_type, {{secret_type, x}});
        m = m.declare (symbol {"Valid"}, integer_type, {{pubkey_type, x}});

        m = m.declare (symbol {"ToPublic"}, pubkey_type, {{secret_type, x}});

        m = m.declare (symbol {"Compress"}, pubkey_type, {{pubkey_type, x}});
        m = m.declare (symbol {"Deompress"}, pubkey_type, {{pubkey_type, x}});

        m = m.declare (symbol {"Compressed"}, bool_type, {{pubkey_type, x}});
        m = m.declare (symbol {"Unceompressed"}, bool_type, {{pubkey_type, x}});

        m = m.declare (binary_operand::plus, pubkey_type, {pubkey_type, x}, {pubkey_type, y});
        m = m.declare (binary_operand::times, pubkey_type, {secret_type, x}, {pubkey_type, y});
        m = m.declare (binary_operand::times, pubkey_type, {pubkey_type, x}, {secret_type, y});

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

        // base 58
        m = m.declare (symbol {"ReadBase58"}, secret_type, {{string_type, x}});
        m = m.declare (symbol {"WriteBase58"}, string_type, {{secret_type, x}});

        // base 58 check
        m = m.declare (symbol {"ReadBase58Check"}, integer_type, {{string_type, x}});
        m = m.declare (symbol {"WriteBase58Check"}, string_type, {{integer_type, x}});

        // make a random key using the given string as extra entropy.
        m = m.declare (symbol {"RandomKey"}, secret_type, {{integer_type, x}});
        m = m.declare (symbol {"RandomKey"}, secret_type, {{string_type, x}});

        // advanced math
        m = m.declare (symbol {"Inverse"}, secret_type, {secret_type, x});

        m = m.declare (binary_operand::divide, secret_type, {secret_type, x}, {secret_type, y});

        // power
        m = m.declare (binary_operand::power, secret_type, {secret_type, x}, {secret_type, y});

        m = m.declare (symbol {"Power"}, secret_type, {{secret_type, x}, {secret_type, y}});

        m = m.declare (binary_operand::power, integer_type, integer_type, secret_type);

        m = m.declare (symbol {"Power"}, integer_type, {{secret_type, x}, {secret_type, y}});

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

    Bitcoin::integer secret_unequal (const secp256k1::secret &x, const secp256k1::secret &y) {
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

    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const secp256k1::secret &y) {
        return Bitcoin::integer {extend (x, size_t (y.Value))};
    }

    data::string string_cat (const data::string &x, const data::string &y) {
        return Bitcoin::cat (x, y);
    }

    data::string string_left (const data::string &x, const Bitcoin::integer &y) {
        return data::string {Bitcoin::left (x, static_cast<size_t> (data::int64 (y)))};
    }

    data::string string_left (const data::string &x, const secp256k1::secret &y) {
        return data::string {Bitcoin::left (x, size_t (y.Value))};
    }

    data::string string_right (const data::string &x, const Bitcoin::integer &y) {
        return data::string {Bitcoin::right (x, static_cast<size_t> (data::int64 (y)))};
    }

    data::string string_right (const data::string &x, const secp256k1::secret &y) {
        return data::string {Bitcoin::right (x, size_t (y.Value))};
    }

    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {Bitcoin::left (x, static_cast<size_t> (data::int64 (y)))};
    }

    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const secp256k1::secret &y) {
        return Bitcoin::integer {Bitcoin::left (x, size_t (y.Value))};
    }

    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {Bitcoin::right (x, static_cast<size_t> (data::int64 (y)))};
    }

    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const secp256k1::secret &y) {
        return Bitcoin::integer {Bitcoin::right (x, size_t (y.Value))};
    }

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::left_shift (x, static_cast<size_t> (data::int64 (y)));
    }

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const secp256k1::secret &y) {
        return Bitcoin::left_shift (x, size_t (y.Value));
    }

    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::right_shift (x, static_cast<size_t> (data::int64 (y)));
    }

    Bitcoin::integer scriptnum_shift_right (const Bitcoin::integer &x, const secp256k1::secret &y) {
        return Bitcoin::right_shift (x, size_t (y.Value));
    }

    Bitcoin::integer pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return x == y;
    }

    Bitcoin::integer pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return x != y;
    }

    Bitcoin::integer pubkey_unqual (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return static_cast<const data::bytes &> (x) == static_cast<const data::bytes &> (y);
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

