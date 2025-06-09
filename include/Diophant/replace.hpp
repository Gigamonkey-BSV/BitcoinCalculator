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
    template <typename result_type>
    struct intuit_result : data::either<result_type, intuit> {
        intuit_result (intuit i): data::either<result_type, intuit> {i} {}
        intuit_result (const result_type &r): data::either<result_type, intuit> {r} {}

        operator intuit () const {
            if (std::holds_alternative<result_type> (*this)) return yes;
            return std::get<intuit> (*this);
        }

        result_type operator * () const {
            if (std::holds_alternative<result_type> (*this)) return std::get<result_type> (*this);
            if (std::get<intuit> (*this) == yes) return result_type {};
            throw data::exception {} << "No result";
        }

        constexpr result_type *operator -> () {
            return this->template get_if<result_type> ();
        }

        constexpr result_type *operator -> () const {
            return this->template get_if<result_type> ();
        }
    };

    using match_result = intuit_result<replacements>;

    template <typename result_type>
    std::ostream &operator << (std::ostream &o, intuit_result<result_type> mr);

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

    template <typename result_type>
    std::ostream inline &operator << (std::ostream &o, intuit_result<result_type> mr) {
        if (std::holds_alternative<intuit> (mr)) return o << std::get<intuit> (mr);
        return o << "yes: " << std::get<result_type> (mr);
    }

}

#endif
