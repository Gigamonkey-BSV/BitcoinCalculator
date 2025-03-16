#ifndef BITCOIN_CALCULATOR_MATCH
#define BITCOIN_CALCULATOR_MATCH

#include <type.hpp>
#include <pattern.hpp>
#include <replace.hpp>

namespace Diophant {

    struct cast : node {
        type Type;
        expression Expr;
        static expression make (const type &, Expression);
    };

    maybe<replacements> match (stack<pattern>, stack<expression>, stack<cast> known = {});

}

#endif

