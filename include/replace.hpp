#ifndef BITCOIN_CALCULATOR_REPLACE
#define BITCOIN_CALCULATOR_REPLACE

#include <symbol.hpp>

namespace Diophant {

    using replacements = map<symbol, expression>;

    expression replace (expression, replacements);

}

#endif
