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

    struct node : form {
        virtual ~node () {}
    };

    struct expression : data::ptr<const node> {
        // a nil expression
        expression (): data::ptr<const node> {} {}
        expression (data::ptr<const node> x): data::ptr<const node> {x} {}
    };

    using Expression = const expression &;

    bool operator == (Expression, Expression);

    std::ostream &operator << (std::ostream &, Expression);

}

#endif
