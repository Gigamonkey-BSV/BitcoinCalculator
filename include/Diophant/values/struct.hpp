#ifndef BITCOIN_CALCULATOR_VALUES_STRUCT
#define BITCOIN_CALCULATOR_VALUES_STRUCT

#include <Diophant/value.hpp>

namespace Diophant {

    struct dstruct final : value {
        data::stack<data::entry<symbol, expression>> Values;

        dstruct (data::stack<data::entry<symbol, expression>> l) : Values {l} {}
        static expression make (data::stack<data::entry<symbol, expression>>);

        bool cast (const machine &, const node &) const final override;
        bool operator == (const node &) const final override;

        std::ostream &write (std::ostream &o) const final override {
            o << "{";
            auto b = Values.begin ();
            if (b != Values.end ()) {
                o << b->Key << " -> " << b->Value;
                while (true) {
                    b++;
                    if (b == Values.end ()) break;
                    o << ", " << b->Key << " -> " << b->Value;
                }
            }
            return o << "}";
        }
    };

    expression inline dstruct::make (data::stack<data::entry<symbol, expression>> v) {
        return expression {std::static_pointer_cast<form> (std::make_shared<dstruct> (v))};
    }

    bool inline dstruct::cast (const machine &, const node &) const {
        throw data::exception {} << "incomplete method dstruct::cast";
    }

    bool inline dstruct::operator == (const node &v) const {
        if (const dstruct *d = dynamic_cast<const dstruct *> (&v); d != nullptr)
            return Values == d->Values;
        return false;
    }

}

#endif


