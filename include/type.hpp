#ifndef BITCOIN_CALCULATOR_TYPE
#define BITCOIN_CALCULATOR_TYPE

#include <expression.hpp>

namespace Diophant {

    struct type;

    using Type = const type &;

    struct type : expression {
        // any type
        type () : expression {} {}
        type (expression);

        bool operator == (Type) const;
        bool operator < (Type) const;
        bool operator > (Type) const;
        bool operator <= (Type) const;
        bool operator >= (Type) const;
    };

    using statement = type;

    enum class impartial_ordering {
        equal,
        disjoint,
        subset,
        superset,
        nonempty_complements
    };

    impartial_ordering operator <=> (Type, Type);

    bool inline type::operator == (Type t) const {
        return (*this <=> t) == impartial_ordering::equal;
    }

    bool inline type::operator < (Type t) const {
        return (*this <=> t) == impartial_ordering::subset;
    }

    bool inline type::operator > (Type t) const {
        return (*this <=> t) == impartial_ordering::superset;
    }

    bool inline type::operator <= (Type t) const {
        auto x = (*this <=> t);
        return x == impartial_ordering::equal || x == impartial_ordering::subset;
    }

    bool inline type::operator >= (Type t) const {
        auto x = (*this <=> t);
        return x == impartial_ordering::equal || x == impartial_ordering::superset;
    }

    inline type::type (expression e) {
        static_cast<expression &> (*this) = e;
    }

}

#endif

