#ifndef BITCOIN_CALCULATOR_VALUES_LAMBDA
#define BITCOIN_CALCULATOR_VALUES_LAMBDA

#include <Diophant/value.hpp>

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
        o << "(@";
        for (const symbol &x : Args) o << " " << x;
        return o << " -> " << Body << ")";
    }

    bool inline lambda::operator == (const node &n) const {
        const lambda *ll = dynamic_cast<const lambda *> (&n);
        if (ll == nullptr || data::size (Args) != data::size (ll->Args)) return false;
        return replace (Body, data::fold ([] (auto &&rep, auto &&entry) {
            return rep.insert (entry);
        }, replacements {}, data::map_thread ([] (auto &&left, auto &&right) {
            return data::entry<const symbol, expression> {left, symbol::make (right)};
        }, Args, ll->Args))) == ll->Body;
    }

}

#endif
