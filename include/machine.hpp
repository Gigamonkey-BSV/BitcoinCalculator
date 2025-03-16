#ifndef BITCOIN_CALCULATOR_MACHINE
#define BITCOIN_CALCULATOR_MACHINE

#include <nodes.hpp>
#include <match.hpp>

namespace Diophant {

    template <typename K, typename V> using map = data::map<K, V>;
    template <typename... X> using either = data::either<X...>;

    struct machine {

        machine define (symbol, type, expression) const;
        machine define (symbol, type, stack<pattern>, expression) const;

        machine define (unary_operator, type, pattern, expression) const;
        machine define (binary_operator, type, pattern, pattern, expression) const;

        machine declare (symbol, type) const;
        machine declare (symbol, type, stack<pattern>) const;

        machine declare (unary_operator, type, pattern) const;
        machine declare (binary_operator, type, pattern, pattern) const;

        bool valid () const;

        expression evaluate (Expression) const;

        // last result calculated by the machine.
        expression Last;

        bool operator == (const machine &) const;

        struct transformation {
            stack<pattern> Arguments;
            expression Value;

            // throws exception if two transformations
            // are not either disjoint or one is a subset of the other.
            std::partial_ordering operator <=> (const transformation) const;
        };

        using definition = either<expression, data::ordered_list<transformation>>;

        map<symbol, definition> SymbolDefinitions;
        map<unary_operator, definition> UnaryDefinitions;
        map<binary_operator, definition> BinaryDefinitions;
    };

    machine initialize ();

}

#endif

