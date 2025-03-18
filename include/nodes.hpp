#ifndef BITCOIN_CALCULATOR_NODES
#define BITCOIN_CALCULATOR_NODES

#include <expression.hpp>
#include <operators.hpp>

namespace Diophant {

    struct call : node {
        expression Fun;
        data::list<expression> Args;

        call (expression fun, data::list<expression> args);

        static expression make (expression fun, data::list<expression> args);
    };

    struct unary_operation : node {
        unary_operand Operator;
        expression Body;

        unary_operation (unary_operand op, expression body);

        static expression make (unary_operand op, expression body);
    };

    struct binary_operation : node {
        binary_operand Operator;
        expression Left;
        expression Right;

        binary_operation (binary_operand op, expression left, expression right);

        static expression make (binary_operand op, expression left, expression right);
    };

    expression inline call::make (expression fun, data::list<expression> args) {
        return expression {std::static_pointer_cast<const node> (std::make_shared<call> (fun, args))};
    }

    expression inline unary_operation::make (unary_operand op, expression body) {
        return expression {std::static_pointer_cast<const node> (std::make_shared<unary_operation> (op, body))};
    }

    expression inline binary_operation::make (binary_operand op, expression left, expression right) {
        return expression {std::static_pointer_cast<const node> (std::make_shared<binary_operation> (op, left, right))};
    }

    inline call::call (expression fun, data::list<expression> args): Fun {fun}, Args {args} {}

    inline unary_operation::unary_operation (unary_operand op, expression body): Operator {op}, Body {body} {}

    inline binary_operation::binary_operation (binary_operand op, expression left, expression right): Operator {op}, Left {left}, Right {right} {}

}

#endif

