#ifndef BITCOIN_CALCULATOR_MACHINE
#define BITCOIN_CALCULATOR_MACHINE

#include <pattern.hpp>
#include <nodes.hpp>

namespace Diophant {

    struct transformation {
        stack<pattern> Arguments;
        expression Value;
    };

    struct definition : data::either<expression, stack<transformation>> {};

    struct machine {
        data::map<symbol, definition> SymbolDefinitions;
        data::map<unary_operator, definition> UnaryDefinitions;
        data::map<binary_operator, definition> BinaryDefinitions;

        machine define (symbol, expression) const;
        machine define (symbol, const transformation &) const;

        machine define (unary_operator, expression) const;
        machine define (unary_operator, const transformation &) const;

        machine define (binary_operator, expression);
        machine define (binary_operator, const transformation &) const;

        bool valid () const;

        machine evaluate (expression);

        // last result calculated by the machine.
        expression Last;

        bool operator == (const machine &) const;
    };

    machine initialize ();

}

#endif

