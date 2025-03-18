#ifndef BITCOIN_CALCULATOR_PATTERN
#define BITCOIN_CALCULATOR_PATTERN

#include <symbol.hpp>
#include <type.hpp>

namespace Diophant {

    struct pattern : data::ptr<const form> {

        pattern (const expression);
        // a blank pattern.
        pattern ();
        // a pattern that matches a given type.
        pattern (const type &);
        // a symbol that matches anything.
        pattern (Symbol);
        // a symbol of a particular type.
        pattern (Symbol, const type &);

        pattern (data::ptr<const form> x): data::ptr<const form> {x} {}
    };

    using Pattern = const pattern &;

    bool operator == (Pattern, Pattern);

    // matches everything.
    struct blank : form {
        symbol Name;

        blank ();
        blank (Symbol x);

        static pattern make ();
        static pattern make (Symbol);
    };

    // matches things of a given type.
    struct typed : form {
        pattern Match;
        type Required;

        typed (Pattern m, Type r): Match {m}, Required {r} {}

        static pattern make (Pattern, Type);
    };

    // a blank pattern.
    inline pattern::pattern (): data::ptr<const form> {} {
        *this = blank::make ();
    }

    // a pattern that matches a given type.
    inline pattern::pattern (Type t): data::ptr<const form> {} {
        *this = typed::make (blank::make (), t);
    }

    // a symbol that matches anything.
    inline pattern::pattern (Symbol x): data::ptr<const form> {} {
        *this = blank::make (x);
    }

    // a symbol of a particular type.
    inline pattern::pattern (Symbol x, Type t): data::ptr<const form> {} {
        *this = typed::make (blank::make (x), t);
    }

    inline blank::blank (): form {}, Name {} {}
    inline blank::blank (Symbol x): form {}, Name {x} {}

    pattern inline blank::make () {
        return pattern {std::static_pointer_cast<const form> (std::make_shared<blank> ())};
    }

    pattern inline blank::make (Symbol x) {
        return pattern {std::static_pointer_cast<const form> (std::make_shared<blank> (x))};
    }

    pattern inline typed::make (Pattern p, Type t) {
        return pattern {std::static_pointer_cast<const form> (std::make_shared<typed> (p, t))};
    }

}

#endif

