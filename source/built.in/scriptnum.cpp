
#include <built.in/scriptnum.hpp>
#include <gigamonkey/p2p/checksum.hpp>

namespace Diophant {

    Bitcoin::integer scriptnum_bool_not (const Bitcoin::integer &x) {
        return !x;
    }

    Bitcoin::integer scriptnum_bool_and (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x && y;
    }

    Bitcoin::integer scriptnum_bool_or (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x || y;
    }

    Bitcoin::integer scriptnum_bit_not (const Bitcoin::integer &x) {
        Bitcoin::integer z;
        z.resize (x.size ());
        for (int i = 0; i < z.size (); i++) z[i] = ~x[i];
        return z;
    }

    Bitcoin::integer scriptnum_bit_and (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        if (x.size () != y.size ()) throw data::exception {"BitAnd called on strings of different sizes"};
        Bitcoin::integer z;
        z.resize (x.size ());
        for (int i = 0; i < z.size (); i++) z[i] = x[i] & y[i];
        return z;
    }

    Bitcoin::integer scriptnum_bit_xor (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        if (x.size () != y.size ()) throw data::exception {"BitAnd called on strings of different sizes"};
        Bitcoin::integer z;
        z.resize (x.size ());
        for (int i = 0; i < z.size (); i++) z[i] = x[i] ^ y[i];
        return z;
    }

    Bitcoin::integer scriptnum_bit_or (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        if (x.size () != y.size ()) throw data::exception {"BitAnd called on strings of different sizes"};
        Bitcoin::integer z;
        z.resize (x.size ());
        for (int i = 0; i < z.size (); i++) z[i] = x[i] | y[i];
        return z;
    }

    Bitcoin::integer scriptnum_identical (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {data::identical (x, y)};
    }

    Bitcoin::integer scriptnum_equal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x == y;
    }

    Bitcoin::integer scriptnum_unequal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x != y;
    }

    Bitcoin::integer scriptnum_greater_equal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x >= y;
    }

    Bitcoin::integer scriptnum_less_equal (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x <= y;
    }

    Bitcoin::integer scriptnum_greater (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x > y;
    }

    Bitcoin::integer scriptnum_less (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x < y;
    }

    Bitcoin::integer scriptnum_negate (const Bitcoin::integer &x) {
        return -x;
    }

    Bitcoin::integer scriptnum_plus (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x + y;
    }

    Bitcoin::integer scriptnum_minus (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x - y;
    }

    Bitcoin::integer scriptnum_times (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x * y;
    }

    Bitcoin::integer scriptnum_divide (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x / y;
    }

    Bitcoin::integer scriptnum_mod (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return x % y;
    }

    Bitcoin::integer scriptnum_size (const Bitcoin::integer &x) {
        return Bitcoin::integer {x.size ()};
    }

    Bitcoin::integer scriptnum_is_minimal (const Bitcoin::integer &x) {
        return Bitcoin::integer {is_minimal (x)};
    }

    Bitcoin::integer scriptnum_minimal_size (const Bitcoin::integer &x) {
        return Bitcoin::integer {minimal_size (x)};
    }

    Bitcoin::integer scriptnum_minimal (const Bitcoin::integer &x) {
        return Bitcoin::integer {trim (x)};
    }

    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {extend (x, static_cast<size_t> (data::int64 (y)))};
    }

    Bitcoin::integer scriptnum_cat (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::cat (x, y);
    }

    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {Bitcoin::left (x, static_cast<size_t> (data::int64 (y)))};
    }

    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::integer {Bitcoin::right (x, static_cast<size_t> (data::int64 (y)))};
    }

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::left_shift (x, static_cast<size_t> (data::int64 (y)));
    }

    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return Bitcoin::right_shift (x, static_cast<size_t> (data::int64 (y)));
    }

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return data::pow (x, y);
    }

    std::tuple<Bitcoin::integer, Bitcoin::integer> scriptnum_split (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        auto sp = Bitcoin::split (x, static_cast<size_t> (data::int64 (y)));
        return {Bitcoin::integer::read (sp.first), Bitcoin::integer::read (sp.second)};
    }

    Bitcoin::integer bitcoin_checksum (const Bitcoin::integer &x) {
        return Bitcoin::integer::read (bitcoin_checksum (x));
    }

}
