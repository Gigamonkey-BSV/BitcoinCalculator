#ifndef BITCOIN_CALCULATOR_SYMBOL
#define BITCOIN_CALCULATOR_SYMBOL

#include <Diophant/expression.hpp>

namespace Diophant {

    struct symbol final : node, std::string {
        symbol (): node {}, std::string {} {}
        symbol (const std::string &x): node {}, std::string {x} {}

        static expression make (const std::string &);

        bool operator == (const node &n) const final override;

        bool operator == (const symbol &x) const;
        std::strong_ordering operator <=> (const symbol &x) const;
    };

    using Symbol = const symbol &;

    expression inline symbol::make (const std::string &x) {
        return expression {std::static_pointer_cast<form> (std::make_shared<symbol> (x))};
    }

    bool inline symbol::operator == (const node &n) const {
        if (const symbol *x = dynamic_cast<const symbol *> (&n); x != nullptr &&
            static_cast<const std::string &> (*this) == static_cast<const std::string &> (*x)) return true;
        return false;
    };

    bool inline symbol::operator == (const symbol &x) const {
        return static_cast<const std::string &> (*this) == static_cast<const std::string &> (x);
    }

    std::strong_ordering inline symbol::operator <=> (const symbol &x) const {
        return static_cast<const std::string &> (*this) <=> static_cast<const std::string &> (x);
    }

}

#endif
