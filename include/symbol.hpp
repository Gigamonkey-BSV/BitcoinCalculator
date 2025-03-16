#ifndef BITCOIN_CALCULATOR_SYMBOL
#define BITCOIN_CALCULATOR_SYMBOL

#include <expression.hpp>

namespace Diophant {

    struct symbol final : node, std::string {
        using std::string::string;
        static expression make (const std::string &);
    };

}

#endif
