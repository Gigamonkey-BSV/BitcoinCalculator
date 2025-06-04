#include <Diophant/built.in/modular.hpp>

namespace Diophant {

    data::N secp256k1_prime {"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f"};
    data::N secp256k1_order {"0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141"};

    bool secret_valid (const data::N x) {
        return x > 0 && x < secp256k1_order;
    }

    bool coord_valid (const data::N x) {
        return x > 0 && x < secp256k1_prime;
    }

    bool secret_equal (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x == y;
    }

    bool secret_unequal (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x != y;
    }

    bool secret_greater_equal (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x >= y;
    }

    bool secret_less_equal (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x <= y;
    }

    bool secret_greater (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x > y;
    }

    bool secret_less (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return x < y;
    }

    bool coord_equal (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x == y;
    }

    bool coord_unequal (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x != y;
    }

    bool coord_greater_equal (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x >= y;
    }

    bool coord_less_equal (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x <= y;
    }

    bool coord_greater (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x > y;
    }

    bool coord_less (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return x < y;
    }

    data::N secret_negate (const data::N x) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        return data::negate_mod (x, data::math::nonzero {secp256k1_order});
    }

    data::N secret_plus (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return data::plus_mod (x, y, data::math::nonzero {secp256k1_order});
    }

    data::N secret_minus (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return data::minus_mod (x, y, data::math::nonzero {secp256k1_order});
    }

    data::N secret_times (const data::N x, const data::N y) {
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        if (y > secp256k1_order) throw data::exception {} << "invalid secret key value " << y;
        return data::times_mod (x, y, data::math::nonzero {secp256k1_order});
    }

    data::N secret_invert (const data::N x) {
        if (!secret_valid (x)) throw data::exception {} << "invalid secret key value" << x;
        return *data::invert_mod (x, data::math::nonzero {secp256k1_order});
    }

    data::N secret_divide (const data::N x, const data::N y) {
        return secret_times (x, secret_invert (y));
    }

    data::N secret_power (const data::N x, const data::Z &y) {
        if (x == 0) return 0;
        if (y < 0) return data::pow_mod (secret_invert (x), -y, data::math::nonzero {secp256k1_order});
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        return data::pow_mod (x, y, data::math::nonzero {secp256k1_order});
    }

    data::N coord_negate (const data::N x) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        return data::negate_mod (x, data::math::nonzero {secp256k1_prime});
    }

    data::N coord_plus (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return data::plus_mod (x, y, data::math::nonzero {secp256k1_prime});
    }

    data::N coord_minus (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return data::minus_mod (x, y, data::math::nonzero {secp256k1_prime});
    }

    data::N coord_times (const data::N x, const data::N y) {
        if (x > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << x;
        if (y > secp256k1_prime) throw data::exception {} << "invalid coordinate value " << y;
        return data::times_mod (x, y, data::math::nonzero {secp256k1_prime});
    }

    data::N coord_invert (const data::N x) {
        if (!coord_valid (x)) throw data::exception {} << "invalid coordinate value";
        return *data::invert_mod (x, data::math::nonzero {secp256k1_prime});
    }

    data::N coord_divide (const data::N x, const data::N y) {
        return coord_times (x, coord_invert (y));
    }

    data::N coord_power (const data::N x, const data::Z &y) {
        if (x == 0) return 0;
        if (y < 0) return data::pow_mod (coord_invert (x), -y, data::math::nonzero {secp256k1_prime});
        if (x > secp256k1_order) throw data::exception {} << "invalid secret key value " << x;
        return data::pow_mod (x, y, data::math::nonzero {secp256k1_prime});
    }

}
