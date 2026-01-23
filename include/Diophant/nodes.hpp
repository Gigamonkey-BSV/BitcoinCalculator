#ifndef BITCOIN_CALCULATOR_NODES
#define BITCOIN_CALCULATOR_NODES

#include <Diophant/symbol.hpp>
#include <Diophant/operators.hpp>

namespace Diophant {

    struct call : node {
        expression Fun;
        data::stack<expression> Args;

        call (expression fun, data::stack<expression> args);

        static expression make (expression fun, data::stack<expression> args);

        bool operator == (const node &n) const final override {
            const call *gx = dynamic_cast<const call *> (&n);
            return gx != nullptr && this->Fun == gx->Fun && this->Args == gx->Args;
        }
    };

    struct unop : node {
        unary_operand Operand;
        expression Body;

        enum direction {
            left, right
        };

        direction Direction;

        unop (unary_operand op, expression body, direction dir);

        static expression make (unary_operand op, expression body, direction dirs);

        bool operator == (const node &n) const final override {
            const unop *v = dynamic_cast<const unop *> (&n);
            return v == nullptr ? false: this->Operand == v->Operand && this->Direction == v->Direction && this->Body == v->Body;
        }
    };

    struct binop : node {
        binary_operand Operand;
        data::stack<expression> Body;

        binop (binary_operand op, expression left, expression right);
        binop (binary_operand op, data::stack<expression> body);

        static expression make (binary_operand op, expression left, expression right);
        static expression make (binary_operand op, data::stack<expression> body);

        bool operator == (const node &n) const final override {
            const binop *c = dynamic_cast<const binop *> (&n);
            return c == nullptr ? false: this->Operand == c->Operand && this->Body == c->Body;
        }
    };

    struct dif : node {
        expression If;
        expression Then;
        expression Else;

        dif (expression f, expression t, expression e): If {f}, Then {t}, Else {e} {}

        static expression make (expression f, expression t, expression e);

        bool operator == (const node &n) const final override {
            const dif *fi = dynamic_cast<const dif *> (&n);
            return fi == nullptr ? false: this->If == fi->If && this->Then == fi->Then && this->Else == fi->Else;
        }
    };

    struct let : node {
        data::stack<data::entry<const symbol, expression>> Values;
        expression In;

        let (data::stack<data::entry<const symbol, expression>> vals, expression in): Values {vals}, In {in} {}

        static expression make (data::stack<data::entry<const symbol, expression>> vals, expression in);

        bool operator == (const node &n) const final override;
    };

    expression inline call::make (expression fun, data::stack<expression> args) {
        if (args.size () == 0) throw data::exception {} << "call should not be created with empty argument list (for now)";
        return expression {std::static_pointer_cast<form> (std::make_shared<call> (fun, args))};
    }

    expression inline unop::make (unary_operand op, expression body, direction dir) {
        return expression {std::static_pointer_cast<form> (std::make_shared<unop> (op, body, dir))};
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

    inline call::call (expression fun, data::stack<expression> args): Fun {fun}, Args {args} {}

    inline unop::unop (unary_operand op, expression body, direction dir): Operand {op}, Body {body}, Direction {dir} {}

    inline binop::binop (binary_operand op, expression left, expression right): Operand {op}, Body {left, right} {}
    inline binop::binop (binary_operand op, data::stack<expression> body): Operand {op}, Body {body} {}

}

#endif

