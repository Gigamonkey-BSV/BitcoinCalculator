#ifndef BITCOIN_CALCULATOR_EXPRESSION
#define BITCOIN_CALCULATOR_EXPRESSION

#include <Gigamonkey.hpp>
#include <data/maybe.hpp>

namespace Diophant {

    namespace Bitcoin = Gigamonkey::Bitcoin;

    struct machine;
    struct form;

    struct expression : data::ptr<form> {
        // a nil expression
        expression ();
        expression (data::ptr<form> x);

        operator bool () const {
            return this->get () != nullptr;
        }

        expression (const std::string &);
        explicit operator std::string () const;
    };

    using Expression = const expression &;

    bool operator == (Expression, Expression);

    std::ostream &operator << (std::ostream &, Expression);

    std::string write (Expression);

    // includes patterns and symbols as well as concrete expressions.
    struct form {
        virtual ~form () {}
    };

    std::ostream &operator << (std::ostream &, const form *);

    struct node : form {
        virtual ~node () {}

        // if this exists, then an evaluation was already done and this was the result.
        // if the result is null, that means that the expression evaluated to itself.
        mutable data::maybe<expression> Evaluated;

        virtual bool operator == (const node &) const = 0;
    };

    std::ostream inline &operator << (std::ostream &o, Expression p) {
        return o << p.get ();
    }

    inline expression::expression (): data::ptr<form> {} {}
    inline expression::expression (data::ptr<form> x): data::ptr<form> {x} {}

    inline expression::operator std::string () const {
        return write (*this);
    }

}

#endif
