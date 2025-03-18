#ifndef BITCOIN_CALCULATOR_MACHINE
#define BITCOIN_CALCULATOR_MACHINE

#include <nodes.hpp>
#include <pattern.hpp>
#include <replace.hpp>

namespace Diophant {

    struct casted final : node {
        type Cast;

        // if there is no expression, this represents an undefined value.
        data::maybe<expression> Def;

        casted (Type);
        casted (Type, Expression);

        static expression make (Type);
        static expression make (Type, Expression);
    };

    struct machine {

        machine define (symbol x, type of, expression as) const;
        machine define (symbol x, type of, data::stack<pattern> arg, expression as) const;

        machine define (unary_operand op, type of, pattern in, expression as) const;
        machine define (binary_operand op, type of, pattern left, pattern right, expression as) const;

        machine declare (symbol x, type of) const;
        machine declare (symbol x, type of, data::stack<pattern> arg) const;

        machine declare (unary_operand op, type of, pattern in) const;
        machine declare (binary_operand op, type of, pattern left, pattern right) const;

        bool valid () const;

        expression evaluate (Expression) const;

        bool operator == (const machine &) const;

        struct transformation {
            data::stack<pattern> Arguments;
            casted Value;

            // throws exception if two transformations
            // are not either disjoint or one is a subset of the other.
            std::partial_ordering operator <=> (const transformation) const;
        };

        using definition = data::either<expression, casted, data::ordered_list<transformation>>;

        data::map<symbol, definition> SymbolDefinitions;
        data::map<unary_operand, definition> UnaryDefinitions;
        data::map<binary_operand, definition> BinaryDefinitions;

        data::maybe<type> derive_type (Expression) const;

        data::maybe<replacements> match (pattern, expression, data::stack<casted> known = {}) const;
        data::maybe<replacements> match (data::stack<pattern>, data::stack<expression>, data::stack<casted> known = {}) const;

        // try to cast a value as a type.
        data::maybe<casted> cast (const type &, const expression &);
    };

    machine initialize ();

    inline casted::casted (Type t): Cast {t}, Def {} {}

    inline casted::casted (Type t, Expression x): Cast {t}, Def {x} {}

    expression inline casted::make (Type t) {
        return expression {std::static_pointer_cast<const node> (std::make_shared<casted> (t))};
    }

    expression inline casted::make (Type t, Expression x) {
        return expression {std::static_pointer_cast<const node> (std::make_shared<casted> (t, x))};
    }

}

#endif

