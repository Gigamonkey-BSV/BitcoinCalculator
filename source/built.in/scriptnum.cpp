
#include <built.in/scriptnum.hpp>
#include <gigamonkey/p2p/checksum.hpp>

namespace Diophant {

    data::bytes scriptnum_size (const data::bytes &x) {
        return Bitcoin::integer {x.size ()};
    }

    bool scriptnum_minimal (const data::bytes &x) {
        return Bitcoin::is_minimal_number (x);
    }

    data::bytes scriptnum_minimal_size (const data::bytes &x) {
        return Bitcoin::integer {Bitcoin::minimal_number_size (x)};
    }

    data::bytes scriptnum_minimize (const data::bytes &x) {
        auto num = x;
        Bitcoin::trim_number (num);
        return num;
    }

    data::bytes scriptnum_resize (const data::bytes &x, const data::bytes &y) {
        Bitcoin::integer size = Bitcoin::integer::read (y);
        Bitcoin::integer minimal_size {Bitcoin::minimal_number_size (x)};
        if (size < minimal_size) throw data::exception {} << "attempt to trim number below minimal size";
        auto num = x;
        Bitcoin::extend_number (num, static_cast<size_t> (data::int64 (size)));
        return num;
    }

    data::bytes scriptnum_resize (const data::bytes &x, const data::N &y) {
        size_t size = static_cast<size_t> (data::uint64 (y));
        size_t minimal_size {Bitcoin::minimal_number_size (x)};
        if (size < minimal_size) throw data::exception {} << "attempt to trim number below minimal size";
        auto num = x;
        Bitcoin::extend_number (num, size);
        return num;
    }


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

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const Bitcoin::integer &y) {
        return data::pow (x, y);
    }

    Bitcoin::integer scriptnum_abs (const Bitcoin::integer &x) {
        return data::abs (x);
    }

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const data::N &y) {
        return data::pow (x, y);
    }

}
