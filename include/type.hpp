#ifndef BITCOIN_CALCULATOR_TYPE
#define BITCOIN_CALCULATOR_TYPE

#include <expression.hpp>

namespace Diophant {

    struct type : expression {
        type (expression);

        bool operator == (const type &) const;
        bool operator < (const type &) const;
        bool operator > (const type &) const;
        bool operator <= (const type &) const;
        bool operator >= (const type &) const;
    };

    using statement = type;

    enum class impartial_ordering {
        equal,
        unequal,
        subset,
        superset,
        nonempty_complements
    };

    impartial_ordering operator <=> (const type &, const type &);

    bool inline type::operator == (const type &t) const {
        return (*this <=> t) == impartial_ordering::equal;
    }

    bool inline type::operator < (const type &t) const {
        return (*this <=> t) == impartial_ordering::subset;
    }

    bool inline type::operator > (const type &t) const {
        return (*this <=> t) == impartial_ordering::superset;
    }

    bool inline type::operator <= (const type &t) const {
        auto x = (*this <=> t);
        return x == impartial_ordering::equal || x == impartial_ordering::subset;
    }

    bool inline type::operator >= (const type &t) const {
        auto x = (*this <=> t);
        return x == impartial_ordering::equal || x == impartial_ordering::superset;
    }

}

#endif

