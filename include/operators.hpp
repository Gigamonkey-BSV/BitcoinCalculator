#ifndef BITCOIN_CALCULATOR_OPERATORS
#define BITCOIN_CALCULATOR_OPERATORS

namespace Diophant {

    enum class unary_operator {
        tilda,
        plus,
        minus,
        star,
        ampersand,
        exclamation
    };

    enum class binary_operator {
        tilda,
        equal,
        not_equal,
        greater,
        less,
        greater_equal,
        greater_less,
        boolean_and,
        boolean_or,
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

