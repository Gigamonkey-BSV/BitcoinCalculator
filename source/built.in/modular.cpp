#include <built.in/modular.hpp>

namespace Diophant {

    Bitcoin::integer scriptnum_power (const Bitcoin::integer &x, const uint256 &y) {
        return data::pow (x, y);
    }

    Bitcoin::integer scriptnum_left (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::integer {Bitcoin::left (x, size_t (y))};
    }

    Bitcoin::integer scriptnum_right (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::integer {Bitcoin::right (x, size_t (y))};
    }

    Bitcoin::integer scriptnum_left_shift (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::left_shift (x, size_t (y));
    }

    Bitcoin::integer scriptnum_right_shift (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::right_shift (x, size_t (y));
    }

    Bitcoin::integer scriptnum_resize (const Bitcoin::integer &x, const uint256 &y) {
        return Bitcoin::integer {extend (x, size_t (y))};
    }

    uint256 secp256k1_prime {"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f"};
    uint256 secp256k1_order {"0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141"};

    Bitcoin::integer secret_valid (const uint256 &x) {
        return Bitcoin::integer {x > 0 && x < secp256k1_order};
    }

    Bitcoin::integer coord_valid (const uint256 &x) {
        return Bitcoin::integer {x > 0 && x < secp256k1_prime};
    }

    Bitcoin::integer secret_equal (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer secret_unequal (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return Bitcoin::integer {x != y};
    }

    Bitcoin::integer secret_greater_equal (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return Bitcoin::integer {x <= y};
    }

    Bitcoin::integer secret_less_equal (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return Bitcoin::integer {x >= y};
    }

    Bitcoin::integer secret_greater (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return Bitcoin::integer {x < y};
    }

    Bitcoin::integer secret_less (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return Bitcoin::integer {x > y};
    }

    Bitcoin::integer coord_equal (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return Bitcoin::integer {x == y};
    }

    Bitcoin::integer coord_unequal (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return Bitcoin::integer {x != y};
    }

    Bitcoin::integer coord_greater_equal (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return Bitcoin::integer {x <= y};
    }

    Bitcoin::integer coord_less_equal (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return Bitcoin::integer {x >= y};
    }

    Bitcoin::integer coord_greater (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return Bitcoin::integer {x < y};
    }

    Bitcoin::integer coord_less (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return Bitcoin::integer {x > y};
    }

    uint256 secret_negate (const uint256 &x) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        return x == 0 ? 0 : secp256k1_order - x;
    }

    uint256 secret_plus (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return static_cast<uint256> ((uint512 (x) + uint512 (y)) % uint512 (secp256k1_order));
    }

    uint256 secret_minus (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        auto order = uint512 (secp256k1_order);
        return static_cast<uint256> ((uint512 (x) + (order - uint512 (y))) % order);
    }

    uint256 secret_times (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return static_cast<uint256> ((uint512 (x) * uint512 (y)) % uint512 (secp256k1_order));
    }

    uint256 coord_negate (const uint256 &x) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        return x == 0 ? 0 : secp256k1_prime - x;
    }

    uint256 coord_plus (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return static_cast<uint256> ((uint512 (x) + uint512 (y)) % uint512 (secp256k1_prime));
    }

    uint256 coord_minus (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        auto order = uint512 (secp256k1_prime);
        return static_cast<uint256> ((uint512 (x) + (order - uint512 (y))) % order);
    }

    uint256 coord_times (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return static_cast<uint256> ((uint512 (x) * uint512 (y)) % uint512 (secp256k1_prime));
    }

    uint256 secret_invert (const uint256 &x) {
        if (!secret_valid (x)) throw data::exception {} << "invalid secret key value";

        data::N big_order (secp256k1_order);

        data::Z bt =
            data::math::number::euclidian::extended<data::N, data::Z>::algorithm
                (big_order, data::N (x)).BezoutT;

        if (bt < 0) bt += big_order;

        return static_cast<uint256> (data::abs (bt));
    }

    uint256 secret_divide (const uint256 &x, const uint256 &y) {
        return secret_times (x, secret_invert (y));
    }

    uint256 secret_power (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return data::pow_mod (x, y, secp256k1_order);
    }

    uint256 coord_invert (const uint256 &x) {
        if (!coord_valid (x)) throw data::exception {} << "invalid coordinate value";

        data::N big_order (secp256k1_prime);

        data::Z bt =
            data::math::number::euclidian::extended<data::N, data::Z>::algorithm
                (big_order, data::N (x)).BezoutT;

        if (bt < 0) bt += big_order;

        return static_cast<uint256> (data::abs (bt));
    }

    uint256 coord_divide (const uint256 &x, const uint256 &y) {
        return coord_times (x, coord_invert (y));
    }

    uint256 coord_power (const uint256 &x, const uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return data::pow_mod (x, y, secp256k1_order);
    }

}
