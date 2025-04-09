#ifndef BITCOIN_CALCULATOR_VALUES_LIST
#define BITCOIN_CALCULATOR_VALUES_LIST

#include <value.hpp>

namespace Diophant {

    struct list final : value {
        data::stack<expression> List;

        list (data::stack<expression> l) : List {l} {}
        static expression make (data::stack<expression>);

        bool cast (const machine &, const type &) const final override;
        std::ostream &write (std::ostream &) const final override;
        bool operator == (const value &) const final override;
    };

    expression inline list::make (data::stack<expression> x) {
        return expression {std::static_pointer_cast<form> (std::make_shared<list> (x))};
    }

    bool inline list::cast (const machine &, const type &) const {
        throw data::exception {} << "we are not using lists right now";
    }

    bool inline list::operator == (const value &v) const {
        if (const list *c = dynamic_cast<const list *> (&v); c != nullptr)
            return List == c->List;

        return false;
    }

}

#endif

