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

    struct expression : data::ptr<node> {
        // a nil expression
        expression (): data::ptr<node> {} {}
        expression (data::ptr<node> x): data::ptr<node> {x} {}
    };

    using Expression = const expression &;

    bool operator == (Expression, Expression);

    std::ostream &operator << (std::ostream &, Expression);

    std::ostream &operator << (std::ostream &, const form *);

    std::ostream inline &operator << (std::ostream &o, Expression p) {
        return o << static_cast<const form *> (p.get ());
    }

}

#endif
