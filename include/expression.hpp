#ifndef BITCOIN_CALCULATOR_EXPRESSION
#define BITCOIN_CALCULATOR_EXPRESSION

#include <Gigamonkey.hpp>
#include <data/maybe.hpp>

namespace Diophant {

    template <typename X> using maybe = data::maybe<X>;
    template <typename X> using stack = data::stack<X>;
    template <typename K, typename V> using map = data::map<K, V>;
    using exception = data::exception;

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

    bool operator == (const expression &, const expression &);

}

#endif
