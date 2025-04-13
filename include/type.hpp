#ifndef BITCOIN_CALCULATOR_TYPE
#define BITCOIN_CALCULATOR_TYPE

#include <replace.hpp>

namespace Diophant {

    struct type;

    using Type = const type &;

    using statement = type;

    enum class impartial_ordering : data::byte {
        equal = 1,
        disjoint = 2,
        subset = 4,
        superset = 8,
        nonempty_complements = 16
    };

    impartial_ordering compare (Machine, Type, Type);

    impartial_ordering operator ~ (impartial_ordering);

    impartial_ordering operator | (impartial_ordering, impartial_ordering);

    impartial_ordering operator & (impartial_ordering, impartial_ordering);

    impartial_ordering operator && (impartial_ordering, impartial_ordering);

    impartial_ordering inline operator - (impartial_ordering x) {
        return x == impartial_ordering::superset ? impartial_ordering::subset:
            x == impartial_ordering::superset ? impartial_ordering::subset: x;
    }

    struct type : expression {
        // any type
        type () : expression {} {}
        type (expression);

        bool equal (Machine, Type) const;
        bool less (Machine, Type) const;
        bool greater (Machine, Type) const;
        bool less_equal (Machine, Type) const;
        bool greater_equal (Machine, Type) const;

        intuit castable (Machine, Expression) const;

        static impartial_ordering compare (Machine, const node &, Type);
    };

    bool inline type::equal (Machine m, Type t) const {
        return Diophant::compare (m, *this, t) == impartial_ordering::equal;
    }

    bool inline type::less (Machine m, Type t) const {
        return Diophant::compare (m, *this, t) == impartial_ordering::subset;
    }

    bool inline type::greater (Machine m, Type t) const {
        return Diophant::compare (m, *this, t) == impartial_ordering::superset;
    }

    bool inline type::less_equal (Machine m, Type t) const {
        auto n = impartial_ordering::equal | impartial_ordering::subset;
        auto x = Diophant::compare (m, *this, t);
        return data::byte (x & n) && !data::byte (x & ~n);
    }

    bool inline type::greater_equal (Machine m, Type t) const {
        auto n = impartial_ordering::equal | impartial_ordering::superset;
        auto x = Diophant::compare (m, *this, t);
        return data::byte (x & n) && !data::byte (x & ~n);
    }

    inline type::type (expression e) {
        static_cast<expression &> (*this) = e;
    }

    impartial_ordering inline operator ~ (impartial_ordering a) {
        return static_cast<impartial_ordering> (~data::byte (a));
    }

    impartial_ordering inline operator | (impartial_ordering a, impartial_ordering b) {
        return static_cast<impartial_ordering> (data::byte (a) | data::byte (b));
    }

    impartial_ordering inline operator & (impartial_ordering a, impartial_ordering b) {
        return static_cast<impartial_ordering> (data::byte (b) & data::byte (b));
    }

}

#endif

