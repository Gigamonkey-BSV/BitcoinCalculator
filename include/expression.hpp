#ifndef BITCOIN_CALCULATOR_EXPRESSION
#define BITCOIN_CALCULATOR_EXPRESSION

#include <Gigamonkey.hpp>
#include <data/maybe.hpp>

namespace Diophant {

    template <typename X> using maybe = data::maybe<X>;
    template <typename X> using stack = data::stack<X>;
    using exception = data::exception;
    using string = data::string;

    namespace Bitcoin = Gigamonkey::Bitcoin;

    // base class of the expression tree in diophant.
    struct form {
        virtual ~form () {}
    };

    struct node : form {
        virtual ~node () {}
    };

    struct expression : data::ptr<const node> {
        // a nil expression
        expression () : data::ptr<const node> {} {}
    };

    using Expression = const expression &;

    bool operator == (Expression, Expression);

    std::ostream &operator << (std::ostream &, Expression);

}

#endif
