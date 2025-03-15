#ifndef BITCOIN_CALCULATOR_PATTERN
#define BITCOIN_CALCULATOR_PATTERN

#include <symbol.hpp>
#include <type.hpp>

namespace Diophant {

    struct pattern : data::ptr<form> {
        pattern (const expression);
        // a blank pattern.
        pattern ();
        // a pattern that matches a given type.
        pattern (const type &);
        // a symbol that matches anything.
        pattern (const symbol &);
        // a symbol of a particular type.
        pattern (const symbol &, const type &);
    };

}

#endif

