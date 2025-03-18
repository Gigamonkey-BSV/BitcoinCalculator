#ifndef BITCOIN_CALCULATOR_NODES
#define BITCOIN_CALCULATOR_NODES

#include <expression.hpp>
#include <operators.hpp>

namespace Diophant {

    struct call : node {
        expression Fun;
        data::list<expression> Args;
        static expression make (expression fun, data::list<expression> args);
    };

    struct unary_operation : node {
        unary_operand Operator;
        expression Body;
        static expression make (unary_operand op, expression body);
    };

    struct binary_operation : node {
        binary_operand Operator;
        expression Left;
        expression Right;
        static expression make (binary_operand op, expression left, expression right);
    };

}

#endif

