#ifndef BITCOIN_CALCULATOR_VALUES_LIST
#define BITCOIN_CALCULATOR_VALUES_LIST

#include <value.hpp>

namespace Diophant {

    struct list final : value {
        data::stack<expression> List;

        static expression make (data::stack<expression>);

        data::maybe<casted> cast (const machine &, const type &) const final override;
        std::ostream &write (std::ostream &) const final override;
        bool operator == (const value &) const final override;
    };

    expression inline list::make (data::stack<expression>) {
        throw data::exception {} << "we are not using lists right now";
    }

    data::maybe<casted> inline list::cast (const machine &, const type &) const {
        throw data::exception {} << "we are not using lists right now";
    }

    std::ostream inline &list::write (std::ostream &) const {
        throw data::exception {} << "we are not using lists right now";
    }

    bool inline list::operator == (const value &) const {
        throw data::exception {} << "we are not using lists right now";
    }

}

#endif

