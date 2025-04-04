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
        data::stack<expression> Body;

        binary_operation (binary_operand op, expression left, expression right);
        binary_operation (binary_operand op, data::stack<expression> body);

        static expression make (binary_operand op, expression left, expression right);
        static expression make (binary_operand op, data::stack<expression> body);
    };

    expression inline call::make (expression fun, data::list<expression> args) {
        if (args.size () == 0) throw data::exception {} << "call should not be created with empty argument list (for now)";
        return expression {std::static_pointer_cast<form> (std::make_shared<call> (fun, args))};
    }

    expression inline unary_operation::make (unary_operand op, expression body) {
        return expression {std::static_pointer_cast<form> (std::make_shared<unary_operation> (op, body))};
    }

    expression inline binary_operation::make (binary_operand op, expression left, expression right) {
        return expression {std::static_pointer_cast<form> (std::make_shared<binary_operation> (op, left, right))};
    }

    expression inline binary_operation::make (binary_operand op, data::stack<expression> body) {
        return expression {std::static_pointer_cast<form> (std::make_shared<binary_operation> (op, body))};
    }

    inline call::call (expression fun, data::list<expression> args): Fun {fun}, Args {args} {}

    inline unary_operation::unary_operation (unary_operand op, expression body): Operator {op}, Body {body} {}

    inline binary_operation::binary_operation (binary_operand op, expression left, expression right): Operator {op}, Body {left, right} {}
    inline binary_operation::binary_operation (binary_operand op, data::stack<expression> body): Operator {op}, Body {body} {}


}

#endif

