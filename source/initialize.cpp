#include <machine.hpp>
#include <value.hpp>

namespace Diophant {

    machine initialize () {
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

        m = m.declare (unary_operand::bool_not, bool_type, bool_type);
        m = m.declare (binary_operand::bool_and, bool_type, bool_type, bool_type);
        m = m.declare (binary_operand::bool_or, bool_type, bool_type, bool_type);

        // bit operations
        m = m.declare (unary_operand::tilda, integer_type, integer_type);
        m = m.declare (binary_operand::bit_and, integer_type, integer_type, integer_type);
        m = m.declare (binary_operand::bit_or, integer_type, integer_type, integer_type);
        m = m.declare (binary_operand::bit_xor, integer_type, integer_type, integer_type);
        m = m.declare (binary_operand::identical, integer_type, integer_type, integer_type);

        m = m.declare (symbol {"Size"}, integer_type, {integer_type});
        m = m.declare (symbol {"MinimalSize"}, integer_type, {integer_type});
        m = m.declare (symbol {"Resize"}, integer_type, {integer_type});
        m = m.declare (symbol {"Minimal"}, integer_type, {integer_type});
        m = m.declare (symbol {"MinimalQ"}, bool_type, {integer_type});
        m = m.declare (symbol {"RightShift"}, integer_type, {integer_type});
        m = m.declare (symbol {"LeftShift"}, integer_type, {integer_type});

        // arithmetic
        m = m.declare (binary_operand::equal, bool_type, integer_type, integer_type);
        m = m.declare (binary_operand::unequal, bool_type, integer_type, integer_type);
        m = m.declare (binary_operand::greater_equal, bool_type, integer_type, integer_type);
        m = m.declare (binary_operand::less_equal, bool_type, integer_type, integer_type);
        m = m.declare (binary_operand::greater, bool_type, integer_type, integer_type);
        m = m.declare (binary_operand::less, bool_type, integer_type, integer_type);

        m = m.declare (unary_operand::negate, integer_type, integer_type);
        m = m.declare (binary_operand::plus, integer_type, integer_type, integer_type);
        m = m.declare (binary_operand::minus, integer_type, integer_type, integer_type);
        m = m.declare (binary_operand::times, integer_type, integer_type, integer_type);
        m = m.declare (binary_operand::divide, integer_type, integer_type, integer_type);
        m = m.declare (binary_operand::mod, integer_type, integer_type, integer_type);
        m = m.declare (binary_operand::power, integer_type, integer_type, integer_type);
        m = m.declare (symbol {"Power"}, integer_type, {integer_type});

        // string operations
        m = m.declare (binary_operand::cat, integer_type, integer_type, integer_type);

        // secret operations
        m = m.declare (symbol {"Valid"}, integer_type, {secret_type});

        m = m.declare (unary_operand::negate, secret_type, secret_type);

        // plus, minus, times, divide, mod, pow
        m = m.declare (binary_operand::equal, bool_type, secret_type, secret_type);
        m = m.declare (binary_operand::unequal, bool_type, secret_type, secret_type);
        m = m.declare (binary_operand::greater_equal, bool_type, secret_type, secret_type);
        m = m.declare (binary_operand::less_equal, bool_type, secret_type, secret_type);
        m = m.declare (binary_operand::greater, bool_type, secret_type, secret_type);
        m = m.declare (binary_operand::less, bool_type, secret_type, secret_type);

        m = m.declare (unary_operand::negate, secret_type, secret_type);
        m = m.declare (binary_operand::plus, secret_type, secret_type, secret_type);
        m = m.declare (binary_operand::minus, secret_type, secret_type, secret_type);
        m = m.declare (binary_operand::times, secret_type, secret_type, secret_type);
        m = m.declare (binary_operand::divide, secret_type, secret_type, secret_type);
        m = m.declare (binary_operand::mod, secret_type, secret_type, secret_type);
        m = m.declare (binary_operand::power, secret_type, secret_type, secret_type);

        m = m.declare (symbol {"Power"}, secret_type, {secret_type});

        m = m.declare (symbol {"Sign"}, integer_type, {secret_type, integer_type});
        m = m.declare (symbol {"Sign"}, integer_type, {secret_type, secret_type});

        // pubkey operations
        m = m.declare (symbol {"Valid"}, integer_type, {secret_type});
        m = m.declare (binary_operand::equal, bool_type, pubkey_type, pubkey_type);
        m = m.declare (binary_operand::unequal, bool_type, pubkey_type, pubkey_type);

        m = m.declare (binary_operand::plus, pubkey_type, pubkey_type, pubkey_type);
        m = m.declare (binary_operand::times, pubkey_type, secret_type, pubkey_type);
        m = m.declare (binary_operand::times, pubkey_type, pubkey_type, secret_type);

        m = m.declare (symbol {"to_public"}, pubkey_type, {secret_type});

        m = m.declare (symbol {"Verify"}, bool_type, {pubkey_type, integer_type, integer_type});
        m = m.declare (symbol {"Verify"}, bool_type, {pubkey_type, secret_type, integer_type});

        // string operations
        m = m.declare (binary_operand::cat, string_type, string_type, string_type);

        // hash operations
        m = m.declare (symbol {"SHA"}, integer_type, {secret_type, secret_type, integer_type});
        m = m.declare (symbol {"RIPEMD"}, integer_type, {secret_type, integer_type});
        m = m.declare (symbol {"Hash160"}, integer_type, {integer_type});
        m = m.declare (symbol {"Hash256"}, integer_type, {integer_type});

        // base 58 check
        m = m.declare (symbol {"ReadBase58Check"}, integer_type, {string_type});
        m = m.declare (symbol {"WriteBase58Check"}, string_type, {integer_type});

        // base 58
        m = m.declare (symbol {"ReadBase58"}, secret_type, {string_type});
        m = m.declare (symbol {"WriteBase58"}, string_type, {secret_type});

        return m;
    }

}

