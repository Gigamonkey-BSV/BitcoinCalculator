#ifndef BITCOIN_CALCULATOR_MATCH
#define BITCOIN_CALCULATOR_MATCH

#include <type.hpp>
#include <pattern.hpp>

namespace Diophant {

    maybe<replacements> match (pattern, expression, stack<statement> known = {});

}

#endif

