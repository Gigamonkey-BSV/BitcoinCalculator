#ifndef BITCOIN_CALCULATOR_SYMBOL
#define BITCOIN_CALCULATOR_SYMBOL

#include <expression.hpp>

namespace Diophant {

    struct symbol final : node, std::string {
        symbol (): node {}, std::string {} {}
        symbol (const std::string &x): node {}, std::string {x} {}

        static expression make (const std::string &);
    };

    using Symbol = const symbol &;

    expression inline symbol::make (const std::string &x) {
        return expression {std::static_pointer_cast<node> (std::make_shared<symbol> (x))};
    }

}

#endif
