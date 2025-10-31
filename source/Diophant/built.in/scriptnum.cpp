
#include <Diophant/built.in/scriptnum.hpp>
#include <Diophant/built.in/numbers.hpp>
#include <gigamonkey/p2p/checksum.hpp>

namespace Diophant {

    data::bytes cast_bool_to_scriptnum (bool b) {
        return Bitcoin::integer {b};
    }

    data::N cast_scriptnum_to_N (const data::bytes &n) {
        return cast_integer_to_natural (cast_scriptnum_to_Z (n));
    }

    data::Z cast_scriptnum_to_Z (const data::bytes &n) {
        Bitcoin::integer x;
        x.resize (n.size ());
        std::copy (n.begin (), n.end (), x.begin ());
        return data::Z (Bitcoin::integer {x});
    }

    data::bytes cast_N_to_scriptnum (const data::N &n) {
        return Bitcoin::integer (n);
    }

    data::bytes cast_Z_to_scriptnum (const data::Z &z) {
        return Bitcoin::integer (z);
    }

    data::bytes set_sign_bit (const data::bytes &b) {
        if (b.size () == 0) return data::bytes {{0x80}};
        data::bytes bb = b;
        bb[-1] = (bb[-1] & 0x7f) | ((~bb[-1]) & 0x80);
        return bb;
    }

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

    data::bytes scriptnum_bool_not (const data::bytes &x) {
        return Bitcoin::integer {Bitcoin::bool_not (x)};
    }

    data::bytes scriptnum_bool_and (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::integer {Bitcoin::bool_and (x, y)};
    }

    data::bytes scriptnum_bool_or (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::integer {Bitcoin::bool_or (x, y)};
    }

    data::bytes scriptnum_bit_not (const data::bytes &x) {
        return Bitcoin::bit_not (x);
    }

    data::bytes scriptnum_bit_and (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::bit_and (x, y);
    }

    data::bytes scriptnum_bit_xor (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::bit_xor (x, y);
    }

    data::bytes scriptnum_bit_or (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::bit_or (x, y);
    }

    data::bytes scriptnum_identical (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::integer {x == y};
    }

    bool scriptnum_equal (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::num_equal (x, y);
    }

    bool scriptnum_unequal (const data::bytes &x, const data::bytes &y) {
        std::cout << " call scriptnum unequal on " << x << " and " << y << std::endl;
        return Bitcoin::num_not_equal (x, y);
    }

    data::bytes scriptnum_greater_equal (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::integer {Bitcoin::greater_equal (x, y)};
    }

    data::bytes scriptnum_less_equal (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::integer {Bitcoin::less_equal (x, y)};
    }

    data::bytes scriptnum_greater (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::integer {Bitcoin::greater (x, y)};
    }

    data::bytes scriptnum_less (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::integer {Bitcoin::less (x, y)};
    }

    data::bytes scriptnum_negate (const data::bytes &x) {
        return Bitcoin::negate (x);
    }

    data::bytes scriptnum_plus (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::plus (x, y);
    }

    data::bytes scriptnum_minus (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::minus (x, y);
    }

    data::bytes scriptnum_times (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::times (x, y);
    }

    data::bytes scriptnum_divide (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::divide (x, y);
    }

    data::bytes scriptnum_mod (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::mod (x, y);
    }

    data::bytes scriptnum_abs (const data::bytes &x) {
        return Bitcoin::abs (x);
    }

    data::bytes scriptnum_power (const data::bytes &x, const data::bytes &y) {
        data::bytes a = x;
        data::bytes b = y;
        return data::pow (Bitcoin::integer {std::move (a)}, Bitcoin::integer {std::move (b)});
    }

    data::bytes scriptnum_power (const data::bytes &x, const data::N &y) {
        data::bytes a = x;
        return data::pow (Bitcoin::integer {std::move (a)}, Bitcoin::integer {y});
    }

    bool scriptnum_cast_to_bool (const data::bytes &x) {
        return Bitcoin::nonzero (x);
    }

}
