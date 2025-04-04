#ifndef BITCOIN_CALCULATOR_EXPRESSION
#define BITCOIN_CALCULATOR_EXPRESSION

#include <Gigamonkey.hpp>
#include <data/maybe.hpp>

namespace Diophant {

    namespace Bitcoin = Gigamonkey::Bitcoin;

    // includes patterns and symbols as well as concrete expressions.
    struct form {
        virtual ~form () {}
    };

    struct expression : data::ptr<form> {
        // a nil expression
        expression ();
        expression (data::ptr<form> x);
    };

    using Expression = const expression &;

    bool operator == (Expression, Expression);

    std::ostream &operator << (std::ostream &, Expression);

    std::ostream &operator << (std::ostream &, const form *);

    struct node : form {
        virtual ~node () {}
    };

    std::ostream inline &operator << (std::ostream &o, Expression p) {
        return o << p.get ();
    }

    inline expression::expression (): data::ptr<form> {} {}
    inline expression::expression (data::ptr<form> x): data::ptr<form> {x} {}

}

#endif
