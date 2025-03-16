#ifndef BITCOIN_CALCULATOR_REPLACE
#define BITCOIN_CALCULATOR_REPLACE

#include <symbol.hpp>

namespace Diophant {

    template <typename K, typename V> using map = data::map<K, V>;

    using replacements = map<symbol, expression>;

    expression replace (expression, replacements);

}

#endif
