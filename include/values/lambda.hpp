#ifndef BITCOIN_CALCULATOR_VALUES_LAMBDA
#define BITCOIN_CALCULATOR_VALUES_LAMBDA

#include <value.hpp>

namespace Diophant {

    struct lambda final : value {
        data::stack<symbol> Args;
        expression Body;

        lambda (data::stack<symbol> args, expression body): Args {args}, Body {body} {}
        static expression make (data::stack<symbol> args, expression body);

        bool cast (const machine &, const node &) const final override;
        std::ostream &write (std::ostream &) const final override;
        bool operator == (const node &) const final override;
    };

    expression inline lambda::make (data::stack<symbol> args, expression body) {
        return expression {std::static_pointer_cast<form> (std::make_shared<lambda> (args, body))};
    }

    bool inline lambda::cast (const machine &, const node &) const {
        throw data::exception {} << "we don't know how to cast lambdas right now. ";
    }

    std::ostream inline &lambda::write (std::ostream &o) const {
        o << "@";
        for (const symbol &x : Args) o << " " << x;
        return o << " -> " << Body;
    }

    bool inline lambda::operator == (const node &) const {
        throw data::exception {} << "we don't know how to compare lambdas for equality.";
    }

}

#endif
