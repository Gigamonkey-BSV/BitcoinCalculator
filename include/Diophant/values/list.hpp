#ifndef BITCOIN_CALCULATOR_VALUES_LIST
#define BITCOIN_CALCULATOR_VALUES_LIST

#include <Diophant/value.hpp>

namespace Diophant {

    struct list final : value {
        data::stack<expression> List;

        list (data::stack<expression> l) : List {l} {}
        static expression make (data::stack<expression>);

        bool cast (const machine &, const node &) const final override;
        std::ostream &write (std::ostream &) const final override;
        bool operator == (const node &) const final override;
    };

    expression inline list::make (data::stack<expression> x) {
        return expression {std::static_pointer_cast<form> (std::make_shared<list> (x))};
    }

    bool inline list::operator == (const node &v) const {
        if (const list *c = dynamic_cast<const list *> (&v); c != nullptr)
            return List == c->List;

        return false;
    }

}

#endif

