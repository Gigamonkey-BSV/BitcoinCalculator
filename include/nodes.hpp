#ifndef BITCOIN_CALCULATOR_NODES
#define BITCOIN_CALCULATOR_NODES

#include <symbol.hpp>
#include <operators.hpp>

namespace Diophant {

    struct call : node {
        expression Fun;
        data::list<expression> Args;

        call (expression fun, data::list<expression> args);

        static expression make (expression fun, data::list<expression> args);
    };

    struct unop : node {
        unary_operand Operand;
        expression Body;

        unop (unary_operand op, expression body);

        static expression make (unary_operand op, expression body);
    };

    struct binop : node {
        binary_operand Operand;
        data::stack<expression> Body;

        binop (binary_operand op, expression left, expression right);
        binop (binary_operand op, data::stack<expression> body);

        static expression make (binary_operand op, expression left, expression right);
        static expression make (binary_operand op, data::stack<expression> body);
    };

    struct dif : node {
        expression If;
        expression Then;
        expression Else;

        dif (expression f, expression t, expression e): If {f}, Then {t}, Else {e} {}

        static expression make (expression f, expression t, expression e);
    };

    struct let : node {
        data::stack<data::entry<const symbol, expression>> Values;
        expression In;

        let (data::stack<data::entry<const symbol, expression>> vals, expression in): Values {vals}, In {in} {}

        static expression make (data::stack<data::entry<const symbol, expression>> vals, expression in);
    };

    expression inline call::make (expression fun, data::list<expression> args) {
        if (args.size () == 0) throw data::exception {} << "call should not be created with empty argument list (for now)";
        return expression {std::static_pointer_cast<form> (std::make_shared<call> (fun, args))};
    }

    expression inline unop::make (unary_operand op, expression body) {
        return expression {std::static_pointer_cast<form> (std::make_shared<unop> (op, body))};
    }

    expression inline binop::make (binary_operand op, expression left, expression right) {
        return expression {std::static_pointer_cast<form> (std::make_shared<binop> (op, left, right))};
    }

    expression inline binop::make (binary_operand op, data::stack<expression> body) {
        return expression {std::static_pointer_cast<form> (std::make_shared<binop> (op, body))};
    }

    expression inline dif::make (expression f, expression t, expression e) {
        return expression {std::static_pointer_cast<form> (std::make_shared<dif> (f, t, e))};
    }

    expression inline let::make (data::stack<data::entry<const symbol, expression>> vals, expression in) {
        return expression {std::static_pointer_cast<form> (std::make_shared<let> (vals, in))};
    }

    inline call::call (expression fun, data::list<expression> args): Fun {fun}, Args {args} {}

    inline unop::unop (unary_operand op, expression body): Operand {op}, Body {body} {}

    inline binop::binop (binary_operand op, expression left, expression right): Operand {op}, Body {left, right} {}
    inline binop::binop (binary_operand op, data::stack<expression> body): Operand {op}, Body {body} {}

}

#endif

