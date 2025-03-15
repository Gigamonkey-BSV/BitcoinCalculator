#include <machine.hpp>
#include <leaves.hpp>

namespace Diophant {

    machine initialize () {
        machine m {};

        // the fundamental types.
        type secret_type {symbol::make ("private")};
        type pubkey_type {symbol::make ("public")};
        type integer_type {symbol::make ("integer")};
        type string_type {symbol::make ("string")};

        // number operations

        // boolean operations
        m = m.declare (unary_operator::exclamation, integer_type, integer_type);
        m = m.declare (binary_operator::bool_and, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::bool_or, integer_type, integer_type, integer_type);

        // bit operations
        m = m.declare (unary_operator::tilda, integer_type, integer_type);
        m = m.declare (binary_operator::bit_and, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::bit_or, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::carot, integer_type, integer_type, integer_type);

        // arithmetic
        m = m.declare (binary_operator::equal, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::unequal, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::greater_equal, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::less_equal, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::greater, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::less, integer_type, integer_type, integer_type);

        m = m.declare (binary_operator::plus, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::minus, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::times, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::divide, integer_type, integer_type, integer_type);
        m = m.declare (binary_operator::mod, integer_type, integer_type, integer_type);

        // string operations
        m = m.declare (binary_operator::join, integer_type, integer_type, integer_type);

        // secret operations
        m = m.declare (unary_operator::negate, secret_type, secret_type);

        // plus, minus, times, divide, mod, pow
        m = m.declare (binary_operator::equal, integer_type, secret_type, secret_type);
        m = m.declare (binary_operator::unequal, integer_type, secret_type, secret_type);
        m = m.declare (binary_operator::greater_equal, integer_type, secret_type, secret_type);
        m = m.declare (binary_operator::less_equal, integer_type, secret_type, secret_type);
        m = m.declare (binary_operator::greater, integer_type, secret_type, secret_type);
        m = m.declare (binary_operator::less, integer_type, secret_type, secret_type);

        m = m.declare (binary_operator::plus, secret_type, secret_type, secret_type);
        m = m.declare (binary_operator::minus, secret_type, secret_type, secret_type);
        m = m.declare (binary_operator::times, secret_type, secret_type, secret_type);
        m = m.declare (binary_operator::divide, secret_type, secret_type, secret_type);
        m = m.declare (binary_operator::mod, secret_type, secret_type, secret_type);
        m = m.declare (binary_operator::carot, secret_type, secret_type, secret_type);

        // pubkey operations
        m = m.declare (binary_operator::equal, integer_type, pubkey_type, pubkey_type);
        m = m.declare (binary_operator::unequal, integer_type, pubkey_type, pubkey_type);

        m = m.declare (binary_operator::plus, pubkey_type, pubkey_type, pubkey_type);
        m = m.declare (binary_operator::times, pubkey_type, secret_type, pubkey_type);
        m = m.declare (binary_operator::times, pubkey_type, pubkey_type, secret_type);

        m = m.declare (symbol {"to_public"}, pubkey_type, {secret_type});

        // string operations
        m = m.declare (binary_operator::join, string_type, string_type, string_type);

        // hash operations
        m = m.declare (symbol {"SHA"}, integer_type, {secret_type, secret_type, integer_type});
        m = m.declare (symbol {"RIPEMD"}, integer_type, {secret_type, integer_type});
        m = m.declare (symbol {"Hash160"}, integer_type, {integer_type});
        m = m.declare (symbol {"Hash256"}, integer_type, {integer_type});

        // base 58 check
        m = m.declare (symbol {"ReadBase58Check"}, integer_type, {string_type});
        m = m.declare (symbol {"WriteBase58Check"}, string_type, {integer_type});

        return m;
    }

}

