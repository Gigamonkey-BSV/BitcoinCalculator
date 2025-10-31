#include <Diophant/built.in/numbers.hpp>
#include <data/power.hpp>

namespace Diophant {

    bool natint_equal (const data::N &x, const data::Z &y) {
        return x == y;
    }

    bool natint_unequal (const data::N &x, const data::Z &y) {
        return x != y;
    }

    data::N cast_integer_to_natural (const data::Z &z) {
        if (z < 0) throw data::exception {} << "cast " << z << " to natural but is negative";
        return data::N (z);
    }

    data::Z cast_natural_to_integer (const data::N &n) {
        return n.Value;
    }

    bool natural_equal (const data::N &x, const data::N &y) {
        return x == y;
    }

    bool natural_unequal (const data::N &x, const data::N &y) {
        return x != y;
    }

    bool natural_greater_equal (const data::N &x, const data::N &y) {
        return x >= y;
    }

    bool natural_less_equal (const data::N &x, const data::N &y) {
        return x <= y;
    }

    bool natural_greater (const data::N &x, const data::N &y) {
        return x > y;
    }

    bool natural_less (const data::N &x, const data::N &y) {
        return x < y;
    }

    bool integer_equal (const data::Z &x, const data::Z &y) {
        return x == y;
    }

    bool integer_unequal (const data::Z &x, const data::Z &y) {
        return x != y;
    }

    bool integer_greater_equal (const data::Z &x, const data::Z &y) {
        return x >= y;
    }

    bool integer_less_equal (const data::Z &x, const data::Z &y) {
        return x <= y;
    }

    bool integer_greater (const data::Z &x, const data::Z &y) {
        return x > y;
    }

    bool integer_less (const data::Z &x, const data::Z &y) {
        return x < y;
    }

    bool uint8_equal (data::byte x, data::byte y) {
        return x == y;
    }

    bool uint8_unequal (data::byte x, data::byte y) {
        return x != y;
    }

    bool uint8_greater_equal (data::byte x, data::byte y) {
        return x >= y;
    }

    bool uint8_less_equal (data::byte x, data::byte y) {
        return x <= y;
    }

    bool uint8_greater (data::byte x, data::byte y) {
        return x > y;
    }

    bool uint8_less (data::byte x, data::byte y) {
        return x < y;
    }

    bool int8_equal (data::int8 x, data::int8 y) {
        return x == y;
    }

    bool int8_unequal (data::int8 x, data::int8 y) {
        return x != y;
    }

    bool int8_greater_equal (data::int8 x, data::int8 y) {
        return x >= y;
    }

    bool int8_less_equal (data::int8 x, data::int8 y) {
        return x <= y;
    }

    bool int8_greater (data::int8 x, data::int8 y) {
        return x > y;
    }

    bool int8_less (data::int8 x, data::int8 y) {
        return x < y;
    }

    bool uint16_equal (data::uint16 x, data::uint16 y) {
        return x == y;
    }

    bool uint16_unequal (data::uint16 x, data::uint16 y) {
        return x != y;
    }

    bool uint16_greater_equal (data::uint16 x, data::uint16 y) {
        return x >= y;
    }

    bool uint16_less_equal (data::uint16 x, data::uint16 y) {
        return x <= y;
    }

    bool uint16_greater (data::uint16 x, data::uint16 y) {
        return x > y;
    }

    bool uint16_less (data::uint16 x, data::uint16 y) {
        return x < y;
    }

    bool int16_equal (data::int16 x, data::int16 y) {
        return x == y;
    }

    bool int16_unequal (data::int16 x, data::int16 y) {
        return x != y;
    }

    bool int16_greater_equal (data::int16 x, data::int16 y) {
        return x >= y;
    }

    bool int16_less_equal (data::int16 x, data::int16 y) {
        return x <= y;
    }

    bool int16_greater (data::int16 x, data::int16 y) {
        return x > y;
    }

    bool int16_less (data::int16 x, data::int16 y) {
        return x < y;
    }

    bool uint32_equal (data::uint32 x, data::uint32 y) {
        return x == y;
    }

    bool uint32_unequal (data::uint32 x, data::uint32 y) {
        return x != y;
    }

    bool uint32_greater_equal (data::uint32 x, data::uint32 y) {
        return x >= y;
    }

    bool uint32_less_equal (data::uint32 x, data::uint32 y) {
        return x <= y;
    }

    bool uint32_greater (data::uint32 x, data::uint32 y) {
        return x > y;
    }

    bool uint32_less (data::uint32 x, data::uint32 y) {
        return x < y;
    }

    bool int32_equal (data::int32 x, data::int32 y) {
        return x == y;
    }

    bool int32_unequal (data::int32 x, data::int32 y) {
        return x != y;
    }

    bool int32_greater_equal (data::int32 x, data::int32 y) {
        return x >= y;
    }

    bool int32_less_equal (data::int32 x, data::int32 y) {
        return x <= y;
    }

    bool int32_greater (data::int32 x, data::int32 y) {return x > y;}

    bool int32_less (data::int32 x, data::int32 y) {
        return x < y;
    }

    bool uint64_equal (data::uint64 x, data::uint64 y) { return x == y; }
    bool uint64_unequal (data::uint64 x, data::uint64 y) { return x != y; }
    bool uint64_greater_equal (data::uint64 x, data::uint64 y) { return x >= y; }
    bool uint64_less_equal (data::uint64 x, data::uint64 y) { return x <= y; }
    bool uint64_greater (data::uint64 x, data::uint64 y) { return x > y; }
    bool uint64_less (data::uint64 x, data::uint64 y) { return x < y; }

    bool int64_equal (data::int64 x, data::int64 y) { return x == y; }
    bool int64_unequal (data::int64 x, data::int64 y) { return x != y; }
    bool int64_greater_equal (data::int64 x, data::int64 y) { return x >= y; }
    bool int64_less_equal (data::int64 x, data::int64 y) { return x <= y; }
    bool int64_greater (data::int64 x, data::int64 y) { return x > y; }
    bool int64_less (data::int64 x, data::int64 y) { return x < y; }

    bool uint128_equal (const data::uint128 &x, const data::uint128 &y) { return x == y; }
    bool uint128_unequal (const data::uint128 &x, const data::uint128 &y) { return x != y; }
    bool uint128_greater_equal (const data::uint128 &x, const data::uint128 &y) { return x >= y; }
    bool uint128_less_equal (const data::uint128 &x, const data::uint128 &y) { return x <= y; }
    bool uint128_greater (const data::uint128 &x, const data::uint128 &y) { return x > y; }
    bool uint128_less (const data::uint128 &x, const data::uint128 &y) { return x < y; }

    bool int128_equal (const data::int128 &x, const data::int128 &y) { return x == y; }
    bool int128_unequal (const data::int128 &x, const data::int128 &y) { return x != y; }
    bool int128_greater_equal (const data::int128 &x, const data::int128 &y) { return x >= y; }
    bool int128_less_equal (const data::int128 &x, const data::int128 &y) { return x <= y; }
    bool int128_greater (const data::int128 &x, const data::int128 &y) { return x > y; }
    bool int128_less (const data::int128 &x, const data::int128 &y) { return x < y; }

    bool uint160_equal (const data::uint160 &x, const data::uint160 &y) { return x == y; }
    bool uint160_unequal (const data::uint160 &x, const data::uint160 &y) { return x != y; }
    bool uint160_greater_equal (const data::uint160 &x, const data::uint160 &y) { return x >= y; }
    bool uint160_less_equal (const data::uint160 &x, const data::uint160 &y) { return x <= y; }
    bool uint160_greater (const data::uint160 &x, const data::uint160 &y) { return x > y; }
    bool uint160_less (const data::uint160 &x, const data::uint160 &y) { return x < y; }

    bool int160_equal (const data::int160 &x, const data::int160 &y) { return x == y; }
    bool int160_unequal (const data::int160 &x, const data::int160 &y) { return x != y; }
    bool int160_greater_equal (const data::int160 &x, const data::int160 &y) { return x >= y; }
    bool int160_less_equal (const data::int160 &x, const data::int160 &y) { return x <= y; }
    bool int160_greater (const data::int160 &x, const data::int160 &y) { return x > y; }
    bool int160_less (const data::int160 &x, const data::int160 &y) { return x < y; }

    bool uint256_equal (const data::uint256 &x, const data::uint256 &y) { return x == y; }
    bool uint256_unequal (const data::uint256 &x, const data::uint256 &y) { return x != y; }
    bool uint256_greater_equal (const data::uint256 &x, const data::uint256 &y) { return x >= y; }
    bool uint256_less_equal (const data::uint256 &x, const data::uint256 &y) { return x <= y; }
    bool uint256_greater (const data::uint256 &x, const data::uint256 &y) { return x > y; }
    bool uint256_less (const data::uint256 &x, const data::uint256 &y) { return x < y; }

    bool int256_equal (const data::int256 &x, const data::int256 &y) { return x == y; }
    bool int256_unequal (const data::int256 &x, const data::int256 &y) { return x != y; }
    bool int256_greater_equal (const data::int256 &x, const data::int256 &y) { return x >= y; }
    bool int256_less_equal (const data::int256 &x, const data::int256 &y) { return x <= y; }
    bool int256_greater (const data::int256 &x, const data::int256 &y) { return x > y; }
    bool int256_less (const data::int256 &x, const data::int256 &y) { return x < y; }

    bool uint512_equal (const data::uint512 &x, const data::uint512 &y) { return x == y; }
    bool uint512_unequal (const data::uint512 &x, const data::uint512 &y) { return x != y; }
    bool uint512_greater_equal (const data::uint512 &x, const data::uint512 &y) { return x >= y; }
    bool uint512_less_equal (const data::uint512 &x, const data::uint512 &y) { return x <= y; }
    bool uint512_greater (const data::uint512 &x, const data::uint512 &y) { return x > y; }
    bool uint512_less (const data::uint512 &x, const data::uint512 &y) { return x < y; }

    bool int512_equal (const data::int512 &x, const data::int512 &y) { return x == y; }
    bool int512_unequal (const data::int512 &x, const data::int512 &y) { return x != y; }
    bool int512_greater_equal (const data::int512 &x, const data::int512 &y) { return x >= y; }
    bool int512_less_equal (const data::int512 &x, const data::int512 &y) { return x <= y; }
    bool int512_greater (const data::int512 &x, const data::int512 &y) { return x > y; }
    bool int512_less (const data::int512 &x, const data::int512 &y) { return x < y; }

    data::byte uint8_plus (data::byte x, data::byte y) { return x + y; }
    data::int8 int8_plus (data::int8 x, data::int8 y) { return x + y; }

    data::byte uint8_minus (data::byte x, data::byte y) { return x - y; }
    data::int8 int8_minus (data::int8 x, data::int8 y) { return x - y; }

    data::byte uint8_times (data::byte x, data::byte y) { return x * y; }
    data::int8 int8_times (data::int8 x, data::int8 y) { return x * y; }

    data::uint16 uint16_plus (data::uint16 x, data::uint16 y) { return x + y; }
    data::int16 int16_plus (data::int16 x, data::int16 y) { return x + y; }

    data::uint16 uint16_minus (data::uint16 x, data::uint16 y) { return x - y; }
    data::int16 int16_minus (data::int16 x, data::int16 y) { return x - y; }

    data::uint16 uint16_times (data::uint16 x, data::uint16 y) { return x * y; }
    data::int16 int16_times (data::int16 x, data::int16 y) { return x * y; }

    data::uint32 uint32_plus (data::uint32 x, data::uint32 y) { return x + y; }
    data::int32 int32_plus (data::int32 x, data::int32 y) { return x + y; }

    data::uint32 uint32_minus (data::uint32 x, data::uint32 y) { return x - y; }
    data::int32 int32_minus (data::int32 x, data::int32 y) { return x - y; }

    data::uint32 uint32_times (data::uint32 x, data::uint32 y) { return x * y; }
    data::int32 int32_times (data::int32 x, data::int32 y) { return x * y; }

    data::byte uint8_bit_and (data::byte x, data::byte y) { return x & y; }
    data::int8 int8_bit_and (data::int8 x, data::int8 y) { return x & y; }

    data::byte uint8_bit_or (data::byte x, data::byte y) { return x | y; }
    data::int8 int8_bit_or (data::int8 x, data::int8 y) { return x | y; }

    data::byte uint8_bit_xor (data::byte x, data::byte y) { return x ^ y; }
    data::int8 int8_bit_xor (data::int8 x, data::int8 y) { return x ^ y; }

    data::uint16 uint16_bit_and (data::uint16 x, data::uint16 y) { return x & y; }
    data::int16 int16_bit_and (data::int16 x, data::int16 y) { return x & y; }

    data::uint16 uint16_bit_or (data::uint16 x, data::uint16 y) { return x | y; }
    data::int16 int16_bit_or (data::int16 x, data::int16 y) { return x | y; }

    data::uint16 uint16_bit_xor (data::uint16 x, data::uint16 y) { return x ^ y; }
    data::int16 int16_bit_xor (data::int16 x, data::int16 y) { return x ^ y; }

    data::uint32 uint32_bit_and (data::uint32 x, data::uint32 y) { return x & y; }
    data::int32 int32_bit_and (data::int32 x, data::int32 y) { return x & y; }

    data::uint32 uint32_bit_or (data::uint32 x, data::uint32 y) { return x | y; }
    data::int32 int32_bit_or (data::int32 x, data::int32 y) { return x | y; }

    data::uint32 uint32_bit_xor (data::uint32 x, data::uint32 y) { return x ^ y; }
    data::int32 int32_bit_xor (data::int32 x, data::int32 y) { return x ^ y; }

    data::Z natural_negate (const data::N &x) {
        return -x;
    }

    data::Z integer_negate (const data::Z &x) {
        return -x;
    }

    data::N integer_abs (const data::Z &x) {
        return data::abs (x);
    }

    data::N natural_plus (const data::N &x, const data::N &y) {
        return x + y;
    }

    data::Z integer_plus (const data::Z &x, const data::Z &y) {
        return x + y;
    }

    data::Z natural_minus (const data::N &x, const data::N &y) {
        return data::Z (x) - data::Z (y);
    }

    data::Z integer_minus (const data::Z &x, const data::Z &y) {
        return x - y;
    }

    data::N natural_times (const data::N &x, const data::N &y) {
        return x * y;
    }

    data::Z integer_times (const data::Z &x, const data::Z &y) {
        return x * y;
    }

    data::N natural_mod (const data::N &x, const data::N &y) {
        return x % y;
    }

    data::N integer_mod (const data::Z &x, const data::N &y) {
        return x % y;
    }

    data::N natural_plus_mod (const data::N &x, const data::N &y, const data::N &z) {
        return data::plus_mod (x, y, data::math::nonzero {z});
    }

    data::N integer_plus_mod (const data::Z &x, const data::Z &y, const data::N &z) {
        return data::plus_mod (x, y, data::math::nonzero {z});
    }

    data::N natural_minus_mod (const data::N &x, const data::N &y, const data::N &z) {
        return data::minus_mod (x, y, data::math::nonzero {z});
    }

    data::N integer_minus_mod (const data::Z &x, const data::Z &y, const data::N &z) {
        return data::minus_mod (x, y, data::math::nonzero {z});
    }

    data::N natural_times_mod (const data::N &x, const data::N &y, const data::N &z) {
        return data::times_mod (x, y, data::math::nonzero {z});
    }

    data::N integer_times_mod (const data::Z &x, const data::Z &y, const data::N &z) {
        return data::times_mod (x, y, data::math::nonzero {z});
    }

    data::N natural_pow_mod (const data::N &x, const data::N &y, const data::N &z) {
        return data::pow_mod (x, y, data::math::nonzero {z});
    }

    data::N integer_pow_mod (const data::Z &x, const data::N &y, const data::N &z) {
        return data::pow_mod (x, y, data::math::nonzero {z});
    }

    data::N natural_power (const data::N &x, const data::N &y) {
        return data::pow (x, y);
    }

    data::Z integer_power (const data::Z &x, const data::N &y) {
        return data::pow (x, y);
    }

    data::byte uint8_negate (data::byte x) {
        return -x;
    }

    data::int8 int8_negate (data::int8 x) {
        return -x;
    }

    data::int8 int8_abs (data::int8 x) {
        return x < 0 ? -x : x;
    }

    data::uint16 uint16_negate (data::uint16 x) {
        return -x;
    }

    data::int16 int16_negate (data::int16 x) {
        return -x;
    }

    data::int16 int16_abs (data::int16 x) {
        return x < 0 ? -x : x;
    }

    data::uint32 uint32_negate (data::uint32 x) {
        return -x;
    }

    data::int32 int32_negate (data::int32 x) {
        return -x;
    }

    data::int32 int32_abs (data::int32 x) {
        return x < 0 ? -x : x;
    }

    data::uint64 uint64_negate (data::uint64 x) {
        return -x;
    }

    data::int64 int64_negate (data::int64 x) {
        return -x;
    }

    data::int64 int64_abs (data::int64 x) {
        return x < 0 ? -x : x;
    }

    data::byte harden (data::byte x) {
        return (x & 0x7f) | ((~x) & 0x80);
    }

    data::uint16 harden (data::uint16 x) {
        return (x & 0x7fff) | ((~x) & 0x8000);
    }

    data::uint32 harden (data::uint32 x) {
        return (x & 0x7fffffff) | ((~x) & 0x80000000);
    }

    data::uint64 harden (data::uint64 x) {
        return (x & 0x7fffffffffffffff) | ((~x) & 0x8000000000000000);
    }

    static_assert (std::same_as<data::uint128, data::math::uint<data::endian::little, 2, data::uint64>>);

    static_assert (std::same_as<data::uint160, data::math::uint<data::endian::little, 5, data::uint32>>);

    static_assert (std::same_as<data::uint256, data::math::uint<data::endian::little, 4, data::uint64>>);

    static_assert (std::same_as<data::uint512, data::math::uint<data::endian::little, 8, data::uint64>>);

    data::uint128 harden (const data::uint128 &x) {
        auto y = x;
        y.words ()[-1] = (y.words ()[-1] & 0x7fffffff) | ((~y.words ()[-1]) & 0x80000000);
        return y;
    }

    data::uint160 harden (const data::uint160 &x) {
        auto y = x;
        y.words ()[-1] = (y.words ()[-1] & 0x7fffffff) | ((~y.words ()[-1]) & 0x80000000);
        return y;
    }

    data::uint256 harden (const data::uint256 &x) {
        auto y = x;
        y.words ()[-1] = (y.words ()[-1] & 0x7fffffff) | ((~y.words ()[-1]) & 0x80000000);
        return y;
    }

    data::uint512 harden (const data::uint512 &x) {
        auto y = x;
        y.words ()[-1] = (y.words ()[-1] & 0x7fffffff) | ((~y.words ()[-1]) & 0x80000000);
        return y;
    }

    using GMP_uint = data::math::number::GMP::gmp_uint;

    static_assert (std::same_as<GMP_uint, data::uint64>);

    data::byte cast_natural_to_byte (const data::N n) {
        if (n > std::numeric_limits<data::byte>::max ()) throw std::out_of_range {""};
        return static_cast<data::byte> (*n.Value.begin ());
    }

    data::int8 cast_natural_to_int8 (const data::N n) {
        if (n > std::numeric_limits<data::int8>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int8> (*n.Value.begin ()) : static_cast<data::int8> (*n.Value.begin ());
    }

    data::uint16 cast_natural_to_uint16 (const data::N n) {
        if (n > std::numeric_limits<data::uint16>::max ()) throw std::out_of_range {""};
        return static_cast<data::uint16> (*n.Value.begin ());
    }

    data::int16 cast_natural_to_int16 (const data::N n) {
        if (n > std::numeric_limits<data::int16>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int16> (*n.Value.begin ()) : static_cast<data::int16> (*n.Value.begin ());
    }

    data::uint32 cast_natural_to_uint32 (const data::N n) {
        if (n > std::numeric_limits<data::uint32>::max ()) throw std::out_of_range {""};
        return static_cast<data::uint32> (*n.Value.begin ());
    }

    data::int32 cast_natural_to_int32 (const data::N n) {
        if (n > std::numeric_limits<data::int32>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int32> (*n.Value.begin ()) : static_cast<data::int32> (*n.Value.begin ());
    }

    data::uint64 cast_natural_to_uint64 (const data::N n) {
        return data::uint64 (n);
    }

    data::int64 cast_natural_to_int64 (const data::N n) {
        if (n > std::numeric_limits<data::int64>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int64> (*n.Value.begin ()) : static_cast<data::int64> (*n.Value.begin ());
    }

    data::uint128 cast_natural_to_uint128 (const data::N n) {
        if (n > data::uint128::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::uint128 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (4)), u.words ().begin ());
        return u;
    }

    data::int128 cast_natural_to_int128 (const data::N n) {
        if (n > data::int128::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::int128 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (4)), u.words ().begin ());
        return u;
    }

    data::uint160 cast_natural_to_uint160 (const data::N n) {
        if (n > data::uint160::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint16> nb (n);
        data::uint160 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (5)), u.words ().begin ());
        return u;
    }

    data::int160 cast_natural_to_int160 (const data::N n) {
        if (n > data::int160::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint16> nb (n);
        data::int160 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (5)), u.words ().begin ());
        return u;
    }

    data::uint256 cast_natural_to_uint256 (const data::N n) {
        if (n > data::uint256::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb {n};
        data::uint256 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (8)), u.words ().begin ());
        return u;
    }

    data::int256 cast_natural_to_int256 (const data::N n) {
        if (n > data::int256::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::int256 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (8)), u.words ().begin ());
        return u;
    }

    data::uint512 cast_natural_to_uint512 (const data::N n) {
        if (n > data::uint512::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::uint512 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (16)), u.words ().begin ());
        return u;
    }

    data::int512 cast_natural_to_int512 (const data::N n) {
        if (n > data::int512::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::int512 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (16)), u.words ().begin ());
        return u;
    }
}
