#ifndef BITCOIN_CALCULATOR_TYPE
#define BITCOIN_CALCULATOR_TYPE

#include <expression.hpp>

namespace Diophant {

    struct type : expression {
        type (expression);
    };

    using statement = type;

}

#endif

