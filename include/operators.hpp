#ifndef BITCOIN_CALCULATOR_OPERATORS
#define BITCOIN_CALCULATOR_OPERATORS

namespace Diophant {

    enum class unary_operator {
        tilda,
        plus,
        negate,
        star,
        ampersand,
        exclamation
    };

    enum class binary_operator {
        join,
        equal,
        unequal,
        greater,
        less,
        greater_equal,
        less_equal,
        bool_and,
        bool_or,
        bit_and,
        bit_or,
        plus,
        minus,
        times,
        carot,
        divide,
        mod,
        colon,
        condition,
        is
    };

}

#endif

