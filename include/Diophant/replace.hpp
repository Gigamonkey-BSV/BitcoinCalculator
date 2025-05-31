#ifndef BITCOIN_CALCULATOR_REPLACE
#define BITCOIN_CALCULATOR_REPLACE

#include <Diophant/symbol.hpp>

namespace Diophant {

    using replacements = data::map<symbol, expression>;

    // replace symbols in exp according to the given replacements.
    expression replace (Expression exp, replacements);

    enum intuit : char {
        unknown = 0,
        yes = 1,
        no = -1
    };

    std::ostream &operator << (std::ostream &o, intuit i);

    // if the pattern matches, we may return replacement
    // rules for symbols. We also need a case where we
    // say that we cannot tell if the pattern matches, so
    // we use intuits as well.
    struct match_result : data::either<replacements, intuit> {
        match_result (intuit i): data::either<replacements, intuit> {i} {}
        match_result (replacements r): data::either<replacements, intuit> {r} {}

        operator intuit () const {
            if (std::holds_alternative<replacements> (*this)) return yes;
            return std::get<intuit> (*this);
        }

        replacements operator * () const {
            if (std::holds_alternative<intuit> (*this) && std::get<intuit> (*this) == yes) return replacements {};
            return std::get<replacements> (*this);
        }
    };

    std::ostream &operator << (std::ostream &o, match_result mr);

    struct machine;
    struct pattern;

    using Pattern = const pattern &;

    using Machine = const machine &;

    // we need a machine because we need to look up definitions.
    match_result match (Machine, Pattern, Expression);

    std::ostream inline &operator << (std::ostream &o, intuit i) {
        if (i == unknown) return o << "unknown";
        if (i == yes) return o << "yes";
        return o << "no";
    }

    std::ostream inline &operator << (std::ostream &o, match_result mr) {
        if (std::holds_alternative<intuit> (mr)) return o << std::get<intuit> (mr);
        return o << "yes: " << std::get<replacements> (mr);
    }

}

#endif
