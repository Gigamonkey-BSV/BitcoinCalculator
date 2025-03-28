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

    struct expression : data::ptr<form> {
        // a nil expression
        expression ();
        expression (data::ptr<node> x);

        node *get ();
        const node *get () const;
    };

    using Expression = const expression &;

    bool operator == (Expression, Expression);

    std::ostream &operator << (std::ostream &, Expression);

    std::ostream &operator << (std::ostream &, const form *);

    std::ostream inline &operator << (std::ostream &o, Expression p) {
        return o << static_cast<const form *> (p.get ());
    }

    inline expression::expression (): data::ptr<form> {} {}
    inline expression::expression (data::ptr<node> x): data::ptr<form> {static_pointer_cast<form> (x)} {}

    node inline *expression::get () {
        return dynamic_cast<node *> (data::ptr<form>::get ());
    }

    const node inline *expression::get () const {
        return dynamic_cast<const node *> (data::ptr<form>::get ());
    }

}

#endif
