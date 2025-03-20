#ifndef BITCOIN_CALCULATOR_VALUES_LAMBDA
#define BITCOIN_CALCULATOR_VALUES_LAMBDA

#include <value.hpp>

namespace Diophant {

    struct lambda final : value {
        data::stack<symbol> Args;
        expression Body;

        static expression make (data::stack<symbol> args, expression body);

        data::maybe<casted> cast (const machine &, const type &) const final override;
        std::ostream &write (std::ostream &) const final override;
        bool operator == (const value &) const final override;
    };

    expression inline lambda::make (data::stack<symbol> args, expression body) {
        throw data::exception {} << "we are not using lambdas right now";
    }

    data::maybe<casted> inline lambda::cast (const machine &, const type &) const {
        throw data::exception {} << "we are not using lambdas right now";
    }

    std::ostream inline &lambda::write (std::ostream &) const {
        throw data::exception {} << "we are not using lambdas right now";
    }

    bool inline lambda::operator == (const value &) const {
        throw data::exception {} << "we are not using lambdas right now";
    }

}

#endif
