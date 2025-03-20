#ifndef BITCOIN_CALCULATOR_PATTERN
#define BITCOIN_CALCULATOR_PATTERN

#include <symbol.hpp>
#include <type.hpp>

namespace Diophant {

    struct pattern : data::ptr<const form> {

        pattern (expression);
        // a blank pattern.
        pattern ();
        // a pattern that matches a given type.
        pattern (Type);
        // a symbol that matches anything.
        pattern (Symbol);
        // a symbol of a particular type.
        pattern (Type, Symbol);

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

        typed (Type r, Pattern m): Match {m}, Required {r} {}

        static pattern make (Type, Pattern);
    };

    // a blank pattern.
    inline pattern::pattern (): data::ptr<const form> {} {
        *this = blank::make ();
    }

    // a pattern that matches a given type.
    inline pattern::pattern (Type t): data::ptr<const form> {} {
        *this = typed::make (t, blank::make ());
    }

    // a symbol that matches anything.
    inline pattern::pattern (Symbol x): data::ptr<const form> {} {
        *this = blank::make (x);
    }

    // a symbol of a particular type.
    inline pattern::pattern (Type t, Symbol x): data::ptr<const form> {} {
        *this = typed::make (t, blank::make (x));
    }

    inline blank::blank (): form {}, Name {} {}
    inline blank::blank (Symbol x): form {}, Name {x} {}

    pattern inline blank::make () {
        return pattern {std::static_pointer_cast<const form> (std::make_shared<blank> ())};
    }

    pattern inline blank::make (Symbol x) {
        return pattern {std::static_pointer_cast<const form> (std::make_shared<blank> (x))};
    }

    pattern inline typed::make (Type t, Pattern p) {
        return pattern {std::static_pointer_cast<const form> (std::make_shared<typed> (t, p))};
    }

    inline pattern::pattern (expression e): pattern {std::static_pointer_cast<const form> (e)} {}

    bool inline operator == (Pattern a, Pattern b) {
        throw data::exception {} << "we cannot check patterns equal yet; pattern.hpp line 87";
    }

}

#endif

