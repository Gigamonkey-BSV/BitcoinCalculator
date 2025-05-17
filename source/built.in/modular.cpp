#include <built.in/modular.hpp>

namespace Diophant {

    data::uint256 secp256k1_prime {"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f"};
    data::uint256 secp256k1_order {"0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141"};

    bool secret_valid (const data::uint256 &x) {
        return x > 0 && x < secp256k1_order;
    }

    bool coord_valid (const data::uint256 &x) {
        return x > 0 && x < secp256k1_prime;
    }

    bool secret_equal (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x == y;
    }

    bool secret_unequal (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x != y;
    }

    bool secret_greater_equal (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x >= y;
    }

    bool secret_less_equal (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x <= y;
    }

    bool secret_greater (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x > y;
    }

    bool secret_less (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x < y;
    }

    bool coord_equal (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x == y;
    }

    bool coord_unequal (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x != y;
    }

    bool coord_greater_equal (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x >= y;
    }

    bool coord_less_equal (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x <= y;
    }

    bool coord_greater (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x > y;
    }

    bool coord_less (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x < y;
    }

    data::uint256 secret_negate (const data::uint256 &x) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        return data::negate_mod (x, data::math::nonzero {secp256k1_order});
    }

    data::uint256 secret_plus (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return data::plus_mod (x, y, data::math::nonzero {secp256k1_order});
    }

    data::uint256 secret_minus (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return data::minus_mod (x, y, data::math::nonzero {secp256k1_order});
    }

    data::uint256 secret_times (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return data::times_mod (x, y, data::math::nonzero {secp256k1_order});
    }

    data::uint256 secret_invert (const data::uint256 &x) {
        if (!secret_valid (x)) throw data::exception {} << "invalid secret key value" << x;
        return *data::invert_mod (x, data::math::nonzero {secp256k1_order});
    }

    data::uint256 secret_divide (const data::uint256 &x, const data::uint256 &y) {
        return secret_times (x, secret_invert (y));
    }

    data::uint256 secret_power (const data::uint256 &x, const data::Z &y) {
        if (x == 0) return 0;
        if (y < 0) return data::pow_mod (secret_invert (x), -y, data::math::nonzero {secp256k1_order});
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        return data::pow_mod (x, y, data::math::nonzero {secp256k1_order});
    }

    data::uint256 coord_negate (const data::uint256 &x) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        return data::negate_mod (x, data::math::nonzero {secp256k1_prime});
    }

    data::uint256 coord_plus (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return data::plus_mod (x, y, data::math::nonzero {secp256k1_prime});
    }

    data::uint256 coord_minus (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return data::minus_mod (x, y, data::math::nonzero {secp256k1_prime});
    }

    data::uint256 coord_times (const data::uint256 &x, const data::uint256 &y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return data::times_mod (x, y, data::math::nonzero {secp256k1_prime});
    }

    data::uint256 coord_invert (const data::uint256 &x) {
        if (!coord_valid (x)) throw data::exception {} << "invalid coordinate value";
        return *data::invert_mod (x, data::math::nonzero {secp256k1_prime});
    }

    data::uint256 coord_divide (const data::uint256 &x, const data::uint256 &y) {
        return coord_times (x, coord_invert (y));
    }

    data::uint256 coord_power (const data::uint256 &x, const data::Z &y) {
        if (x == 0) return 0;
        if (y < 0) return data::pow_mod (coord_invert (x), -y, data::math::nonzero {secp256k1_prime});
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        return data::pow_mod (x, y, data::math::nonzero {secp256k1_prime});
    }

}
