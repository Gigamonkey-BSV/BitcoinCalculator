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

    bool operator == (const pattern &, const pattern &);

    // matches everything.
    struct blank : form {
        symbol Name;
        static pattern make (const symbol &);
    };

    // matches things of a given type.
    struct typed : form {
        pattern Pattern;
        type Type;
        static pattern make (const pattern &, const type &);
    };

}

#endif

