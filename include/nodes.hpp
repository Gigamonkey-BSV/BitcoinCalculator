#ifndef BITCOIN_CALCULATOR_NODES
#define BITCOIN_CALCULATOR_NODES

#include <symbol.hpp>
#include <operators.hpp>

namespace Diophant {

    struct list : node {
        stack<expression> List;
        static expression make (stack<expression>);
    };

    struct call : node {
        expression Fun;
        data::list<expression> Args;
        static expression make (expression fun, data::list<expression> args);
    };

    struct lambda : node {
        stack<symbol> Args;
        expression Body;
        static expression make (stack<symbol> args, expression body);
    };

    struct unary_operation : node {
        unary_operator Operator;
        expression Body;
        static expression make (unary_operator op, expression body);
    };

    struct binary_operation : node {
        binary_operator Operator;
        expression Left;
        expression Right;
        static expression make (binary_operator op, expression left, expression right);
    };

}

#endif

