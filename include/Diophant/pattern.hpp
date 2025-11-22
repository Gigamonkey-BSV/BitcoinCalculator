#ifndef BITCOIN_CALCULATOR_PATTERN
#define BITCOIN_CALCULATOR_PATTERN

#include <Diophant/symbol.hpp>
#include <Diophant/type.hpp>

namespace Diophant {

    struct pattern : expression {

        pattern (expression);
        // a blank pattern.
        pattern ();
        // a pattern that matches a given type.
        pattern (Type);
        // a symbol that matches anything.
        pattern (Symbol);
        // a symbol of a particular type.
        pattern (Type, Symbol);

        pattern (data::ptr<form> x): expression {} {
            *static_cast<data::ptr<form> *> (this) = x;
        }
    };

    using Pattern = const pattern &;

    bool operator == (Pattern, Pattern);

    expression operator | (Expression, Expression);

    impartial_ordering compare (Machine, Pattern, Pattern);

    std::ostream &operator << (std::ostream &, const pattern &);

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

    struct default_value : form {
        pattern Match;
        replacements Default;
        default_value (Pattern m, replacements def): Match {m}, Default {def} {}
        static pattern make (Pattern m, replacements def) {
            return pattern {std::static_pointer_cast<form> (std::make_shared<default_value> (m, def))};
        }
    };

    // a blank pattern.
    inline pattern::pattern (): expression {} {
        *this = blank::make ();
    }

    // a pattern that matches a given type.
    inline pattern::pattern (Type t): expression {} {
        *this = typed::make (t, blank::make ());
    }

    // a symbol that matches anything.
    inline pattern::pattern (Symbol x): expression {} {
        *this = blank::make (x);
    }

    // a symbol of a particular type.
    inline pattern::pattern (Type t, Symbol x): expression {} {
        *this = typed::make (t, blank::make (x));
    }

    inline blank::blank (): form {}, Name {} {}
    inline blank::blank (Symbol x): form {}, Name {x} {}

    pattern inline blank::make () {
        return pattern {std::static_pointer_cast<form> (std::make_shared<blank> ())};
    }

    pattern inline blank::make (Symbol x) {
        return pattern {std::static_pointer_cast<form> (std::make_shared<blank> (x))};
    }

    pattern inline typed::make (Type t, Pattern p) {
        return pattern {std::static_pointer_cast<form> (std::make_shared<typed> (t, p))};
    }

    inline pattern::pattern (expression e): pattern {std::static_pointer_cast<form> (e)} {}

    bool inline operator == (Pattern a, Pattern b) {
        throw data::exception {} << "we cannot check patterns equal yet; pattern.hpp line 87";
    }

    std::ostream inline &operator << (std::ostream &o, const pattern &p) {
        return o << p.get ();
    }

}

#endif

