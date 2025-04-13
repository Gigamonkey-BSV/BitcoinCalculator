#ifndef BITCOIN_CALCULATOR_SYMBOL
#define BITCOIN_CALCULATOR_SYMBOL

#include <expression.hpp>

namespace Diophant {

    struct symbol final : node, std::string {
        symbol (): node {}, std::string {} {}
        symbol (const std::string &x): node {}, std::string {x} {}

        static expression make (const std::string &);

        bool operator == (const node &n) const final override {
            if (const symbol *x = dynamic_cast<const symbol *> (&n); x != nullptr &&
                static_cast<const std::string &> (*this) == static_cast<const std::string &> (*x)) return true;
            return false;
        };

        bool operator == (const symbol &x) const {
            return static_cast<const std::string &> (*this) == static_cast<const std::string &> (x);
        }

        std::strong_ordering operator <=> (const symbol &x) const {
            return static_cast<const std::string &> (*this) <=> static_cast<const std::string &> (x);
        }
    };

    using Symbol = const symbol &;

    expression inline symbol::make (const std::string &x) {
        return expression {std::static_pointer_cast<form> (std::make_shared<symbol> (x))};
    }

}

#endif
