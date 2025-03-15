#ifndef BITCOIN_CALCULATOR_MACHINE
#define BITCOIN_CALCULATOR_MACHINE

#include <pattern.hpp>
#include <nodes.hpp>
#include <type.hpp>

namespace Diophant {


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

        machine evaluate (expression);

        // last result calculated by the machine.
        expression Last;

        bool operator == (const machine &) const;

    private:
        struct transformation {
            stack<pattern> Arguments;
            expression Value;
        };

        struct definition : data::either<expression, stack<transformation>> {};

        data::map<symbol, definition> SymbolDefinitions;
        data::map<unary_operator, definition> UnaryDefinitions;
        data::map<binary_operator, definition> BinaryDefinitions;
    };

    machine initialize ();

}

#endif

