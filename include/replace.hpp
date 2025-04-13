#ifndef BITCOIN_CALCULATOR_REPLACE
#define BITCOIN_CALCULATOR_REPLACE

#include <symbol.hpp>

namespace Diophant {

    using replacements = data::map<symbol, expression>;

    // replace symbols in exp according to the given replacements.
    expression replace (Expression exp, replacements);

    enum intuit : char {
        unknown = 0,
        yes = 1,
        no = -1
    };

    // if the pattern can match, we may return
    // replacement rules for symbols. We also need
    // a case where we say that we cannot tell if the
    // pattern matches.
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

    struct machine;
    struct pattern;

    using Pattern = const pattern &;

    using Machine = const machine &;

    // we need a machine because we need to look up definitions.
    match_result match (Machine, Pattern, Expression);

}

#endif
