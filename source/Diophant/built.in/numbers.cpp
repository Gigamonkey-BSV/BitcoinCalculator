#include <Diophant/built.in/modular.hpp>
#include <data/power.hpp>

namespace Diophant {

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

    bool uint32_little_equal (data::uint32_little x, data::uint32_little y) {return x == y;}

    bool uint32_little_unequal (data::uint32_little x, data::uint32_little y) {
        return x != y;
    }

    bool uint32_little_greater_equal (data::uint32_little x, data::uint32_little y) {
        return x <= y;
    }

    bool uint32_little_less_equal (data::uint32_little x, data::uint32_little y) {
        return x >= y;
    }

    bool uint32_little_greater (data::uint32_little x, data::uint32_little y) {return x > y;}

    bool uint32_little_less (data::uint32_little x, data::uint32_little y) {
        return x < y;
    }

    bool int32_little_equal (data::int32_little x, data::int32_little y) {return x == y;}

    bool int32_little_unequal (data::int32_little x, data::int32_little y) {return x != y;}

    bool int32_little_greater_equal (data::int32_little x, data::int32_little y) {return x >= y;}

    bool int32_little_less_equal (data::int32_little x, data::int32_little y) {return x <= y;}

    bool int32_little_greater (data::int32_little x, data::int32_little y) {return x > y;}

    bool int32_little_less (data::int32_little x, data::int32_little y) {return x < y;}

    bool uint32_big_equal (data::uint32_big x, data::uint32_big y) {return x == y;}

    bool uint32_big_unequal (data::uint32_big x, data::uint32_big y) {return x != y;}

    bool uint32_big_greater_equal (data::uint32_big x, data::uint32_big y) {
        return x >= y;
    }

    bool uint32_big_less_equal (data::uint32_big x, data::uint32_big y) {return x <= y;}

    bool uint32_big_greater (data::uint32_big x, data::uint32_big y) {
        return x > y;
    }

    bool uint32_big_less (data::uint32_big x, data::uint32_big y) {return x < y;}

    bool int32_big_equal (data::int32_big x, data::int32_big y) {
        return x == y;
    }

    bool int32_big_unequal (data::int32_big x, data::int32_big y) {return x != y;}

    bool int32_big_greater_equal (data::int32_big x, data::int32_big y) {return x >= y;}

    bool int32_big_less_equal (data::int32_big x, data::int32_big y) {return x <= y;}

    bool int32_big_greater (data::int32_big x, data::int32_big y) {return x > y;}

    bool int32_big_less (data::int32_big x, data::int32_big y) {return x < y;}

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

    bool uint64_little_equal (data::uint64_little x, data::uint64_little y) { return x == y; }
    bool uint64_little_unequal (data::uint64_little x, data::uint64_little y) { return x != y; }
    bool uint64_little_greater_equal (data::uint64_little x, data::uint64_little y) { return x >= y; }
    bool uint64_little_less_equal (data::uint64_little x, data::uint64_little y) { return x <= y; }
    bool uint64_little_greater (data::uint64_little x, data::uint64_little y) { return x > y; }
    bool uint64_little_less (data::uint64_little x, data::uint64_little y) { return x < y; }

    bool int64_little_equal (data::int64_little x, data::int64_little y) { return x == y; }
    bool int64_little_unequal (data::int64_little x, data::int64_little y) { return x != y; }
    bool int64_little_greater_equal (data::int64_little x, data::int64_little y) { return x >= y; }
    bool int64_little_less_equal (data::int64_little x, data::int64_little y) { return x <= y; }
    bool int64_little_greater (data::int64_little x, data::int64_little y) { return x > y; }
    bool int64_little_less (data::int64_little x, data::int64_little y) { return x < y; }

    bool uint64_big_equal (data::uint64_big x, data::uint64_big y) { return x == y; }
    bool uint64_big_unequal (data::uint64_big x, data::uint64_big y) { return x != y; }
    bool uint64_big_greater_equal (data::uint64_big x, data::uint64_big y) { return x >= y; }
    bool uint64_big_less_equal (data::uint64_big x, data::uint64_big y) { return x <= y; }
    bool uint64_big_greater (data::uint64_big x, data::uint64_big y) { return x > y; }
    bool uint64_big_less (data::uint64_big x, data::uint64_big y) { return x < y; }

    bool int64_big_equal (data::int64_big x, data::int64_big y) { return x == y; }
    bool int64_big_unequal (data::int64_big x, data::int64_big y) { return x != y; }
    bool int64_big_greater_equal (data::int64_big x, data::int64_big y) { return x >= y; }
    bool int64_big_less_equal (data::int64_big x, data::int64_big y) { return x <= y; }
    bool int64_big_greater (data::int64_big x, data::int64_big y) { return x > y; }
    bool int64_big_less (data::int64_big x, data::int64_big y) { return x < y; }

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

    bool uint160_little_equal (const data::uint160_little &x, const data::uint160_little &y) { return x == y; }
    bool uint160_little_unequal (const data::uint160_little &x, const data::uint160_little &y) { return x != y; }
    bool uint160_little_greater_equal (const data::uint160_little &x, const data::uint160_little &y) { return x >= y; }
    bool uint160_little_less_equal (const data::uint160_little &x, const data::uint160_little &y) { return x <= y; }
    bool uint160_little_greater (const data::uint160_little &x, const data::uint160_little &y) { return x > y; }
    bool uint160_little_less (const data::uint160_little &x, const data::uint160_little &y) { return x < y; }

    bool int160_little_equal (const data::int160_little &x, const data::int160_little &y) { return x == y; }
    bool int160_little_unequal (const data::int160_little &x, const data::int160_little &y) { return x != y; }
    bool int160_little_greater_equal (const data::int160_little &x, const data::int160_little &y) { return x >= y; }
    bool int160_little_less_equal (const data::int160_little &x, const data::int160_little &y) { return x <= y; }
    bool int160_little_greater (const data::int160_little &x, const data::int160_little &y) { return x > y; }
    bool int160_little_less (const data::int160_little &x, const data::int160_little &y) { return x < y; }

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

    bool uint256_little_equal (const data::uint256_little &x, const data::uint256_little &y) { return x == y; }
    bool uint256_little_unequal (const data::uint256_little &x, const data::uint256_little &y) { return x != y; }
    bool uint256_little_greater_equal (const data::uint256_little &x, const data::uint256_little &y) { return x >= y; }
    bool uint256_little_less_equal (const data::uint256_little &x, const data::uint256_little &y) { return x <= y; }
    bool uint256_little_greater (const data::uint256_little &x, const data::uint256_little &y) { return x > y; }
    bool uint256_little_less (const data::uint256_little &x, const data::uint256_little &y) { return x < y; }

    bool int256_little_equal (const data::int256_little &x, const data::int256_little &y) { return x == y; }
    bool int256_little_unequal (const data::int256_little &x, const data::int256_little &y) { return x != y; }
    bool int256_little_greater_equal (const data::int256_little &x, const data::int256_little &y) { return x >= y; }
    bool int256_little_less_equal (const data::int256_little &x, const data::int256_little &y) { return x <= y; }
    bool int256_little_greater (const data::int256_little &x, const data::int256_little &y) { return x > y; }
    bool int256_little_less (const data::int256_little &x, const data::int256_little &y) { return x < y; }

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

    bool uint512_little_equal (const data::uint512_little &x, const data::uint512_little &y) { return x == y; }
    bool uint512_little_unequal (const data::uint512_little &x, const data::uint512_little &y) { return x != y; }
    bool uint512_little_greater_equal (const data::uint512_little &x, const data::uint512_little &y) { return x >= y; }
    bool uint512_little_less_equal (const data::uint512_little &x, const data::uint512_little &y) { return x <= y; }
    bool uint512_little_greater (const data::uint512_little &x, const data::uint512_little &y) { return x > y; }
    bool uint512_little_less (const data::uint512_little &x, const data::uint512_little &y) { return x < y; }

    bool int512_little_equal (const data::int512_little &x, const data::int512_little &y) { return x == y; }
    bool int512_little_unequal (const data::int512_little &x, const data::int512_little &y) { return x != y; }
    bool int512_little_greater_equal (const data::int512_little &x, const data::int512_little &y) { return x >= y; }
    bool int512_little_less_equal (const data::int512_little &x, const data::int512_little &y) { return x <= y; }
    bool int512_little_greater (const data::int512_little &x, const data::int512_little &y) { return x > y; }
    bool int512_little_less (const data::int512_little &x, const data::int512_little &y) { return x < y; }

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

    data::uint16_little uint16_little_negate (data::uint16_little x) {
        return -data::uint16 (x);
    }

    data::int16_little int16_little_negate (data::int16_little x) {
        return -x;
    }

    data::int16_little int16_little_abs (data::int16_little x) {
        return x < 0 ? -x : x;
    }

    data::uint32_little uint32_little_negate (data::uint32_little x) {
        return -data::uint32 (x);
    }

    data::int32_little int32_little_negate (data::int32_little x) {
        return -x;
    }

    data::int32_little int32_little_abs (data::int32_little x) {
        return x < 0 ? -x : x;
    }

    data::uint64_little uint64_little_negate (data::uint64_little x) {
        return -data::uint64 (x);
    }

    data::int64_little int64_little_negate (data::int64_little x) {
        return -x;
    }

    data::int64_little int64_little_abs (data::int64_little x) {
        return x < 0 ? -x : x;
    }

    data::uint16_big uint16_big_negate (data::uint16_big x) {
        return -data::uint16 (x);
    }

    data::int16_big int16_big_negate (data::int16_big x) {
        return -x;
    }

    data::int16_big int16_big_abs (data::int16_big x) {
        return x < 0 ? -x : x;
    }

    data::uint32_big uint32_big_negate (data::uint32_big x) {
        return -data::uint32 (x);
    }

    data::int32_big int32_big_negate (data::int32_big x) {
        return -x;
    }

    data::int32_big int32_big_abs (data::int32_big x) {
        return x < 0 ? -x : x;
    }

    data::uint64_big uint64_big_negate (data::uint64_big x) {
        return -data::uint64 (x);
    }

    data::int64_big int64_big_negate (data::int64_big x) {
        return -x;
    }

    data::int64_big int64_big_abs (data::int64_big x) {
        return x < 0 ? -x : x;
    }

    using GMP_uint = data::math::number::GMP::gmp_uint;

    static_assert (std::same_as<GMP_uint, data::uint64>);

    data::byte cast_natural_to_byte (const data::N &n) {
        if (n > std::numeric_limits<data::byte>::max ()) throw std::out_of_range {""};
        return static_cast<data::byte> (*n.Value.begin ());
    }

    data::int8 cast_natural_to_int8 (const data::N &n) {
        if (n > std::numeric_limits<data::int8>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int8> (*n.Value.begin ()) : static_cast<data::int8> (*n.Value.begin ());
    }

    data::uint16 cast_natural_to_uint16 (const data::N &n) {
        if (n > std::numeric_limits<data::uint16>::max ()) throw std::out_of_range {""};
        return static_cast<data::uint16> (*n.Value.begin ());
    }

    data::int16 cast_natural_to_int16 (const data::N &n) {
        if (n > std::numeric_limits<data::int16>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int16> (*n.Value.begin ()) : static_cast<data::int16> (*n.Value.begin ());
    }

    data::uint16_little cast_natural_to_uint16_little (const data::N &n) {
        if (n > std::numeric_limits<data::uint16>::max ()) throw std::out_of_range {""};
        return static_cast<data::uint16> (*n.Value.begin ());
    }

    data::int16_little cast_natural_to_int16_little (const data::N &n) {
        if (n > std::numeric_limits<data::int16>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int16> (*n.Value.begin ()) : static_cast<data::int16> (*n.Value.begin ());
    }

    data::uint16_big cast_natural_to_uint16_big (const data::N &n) {
        if (n > std::numeric_limits<data::uint16>::max ()) throw std::out_of_range {""};
        return static_cast<data::uint16> (*n.Value.begin ());
    }

    data::int16_big cast_natural_to_int16_big (const data::N &n) {
        if (n > std::numeric_limits<data::int16>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int16> (*n.Value.begin ()) : static_cast<data::int16> (*n.Value.begin ());
    }

    data::uint32 cast_natural_to_uint32 (const data::N &n) {
        if (n > std::numeric_limits<data::uint32>::max ()) throw std::out_of_range {""};
        return static_cast<data::uint32> (*n.Value.begin ());
    }

    data::int32 cast_natural_to_int32 (const data::N &n) {
        if (n > std::numeric_limits<data::int32>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int32> (*n.Value.begin ()) : static_cast<data::int32> (*n.Value.begin ());
    }

    data::uint32_little cast_natural_to_uint32_little (const data::N &n) {
        if (n > std::numeric_limits<data::uint32>::max ()) throw std::out_of_range {""};
        return static_cast<data::uint32> (*n.Value.begin ());
    }

    data::int32_little cast_natural_to_int32_little (const data::N &n) {
        if (n > std::numeric_limits<data::int32>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int32> (*n.Value.begin ()) : static_cast<data::int32> (*n.Value.begin ());
    }

    data::uint32_big cast_natural_to_uint32_big (const data::N &n) {
        if (n > std::numeric_limits<data::uint32>::max ()) throw std::out_of_range {""};
        return static_cast<data::uint32> (*n.Value.begin ());
    }

    data::int32_big cast_natural_to_int32_big (const data::N &n) {
        if (n > std::numeric_limits<data::int32>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int32> (*n.Value.begin ()) : static_cast<data::int32> (*n.Value.begin ());
    }

    data::uint64 cast_natural_to_uint64 (const data::N &n) {
        return data::uint64 (n);
    }

    data::int64 cast_natural_to_int64 (const data::N &n) {
        if (n > std::numeric_limits<data::int64>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int64> (*n.Value.begin ()) : static_cast<data::int64> (*n.Value.begin ());
    }

    data::uint64_little cast_natural_to_uint64_little (const data::N &n) {
        return data::uint64 (n);
    }

    data::int64_little cast_natural_to_int64_little (const data::N &n) {
        if (n > std::numeric_limits<data::int64>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int64> (*n.Value.begin ()) : static_cast<data::int64> (*n.Value.begin ());
    }

    data::uint64_big cast_natural_to_uint64_big (const data::N &n) {
        return data::uint64 (n);
    }

    data::int64_big cast_natural_to_int64_big (const data::N &n) {
        if (n > std::numeric_limits<data::uint64>::max ()) throw std::out_of_range {""};
        return n < 0 ? -static_cast<data::int64> (*n.Value.begin ()) : static_cast<data::int64> (*n.Value.begin ());
    }

    static_assert (std::same_as<data::uint128, data::math::uint<data::endian::little, 4, data::uint32>>);

    data::uint128 cast_natural_to_uint128 (const data::N &n) {
        if (n > data::uint128::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::uint128 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (4)), u.words ().begin ());
        return u;
    }

    data::int128 cast_natural_to_int128 (const data::N &n) {
        if (n > data::int128::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::int128 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (4)), u.words ().begin ());
        return u;
    }

    data::uint128_little cast_natural_to_uint128_little (const data::N &n) {
        if (n > data::uint128::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::uint128_little u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (16)), u.words ().begin ());
        return u;
    }

    data::int128_little cast_natural_to_int128_little (const data::N &n) {
        if (n > data::int128::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::int128_little u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (16)), u.words ().begin ());
        return u;
    }

    data::uint128_big cast_natural_to_uint128_big (const data::N &n) {
        if (n > data::uint128::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::uint128_big u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (16)), u.words ().begin ());
        return u;
    }

    data::int128_big cast_natural_to_int128_big (const data::N &n) {
        if (n > data::int128::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::int128_big u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (16)), u.words ().begin ());
        return u;
    }

    static_assert (std::same_as<data::uint160, data::math::uint<data::endian::little, 5, data::uint32>>);

    data::uint160 cast_natural_to_uint160 (const data::N &n) {
        if (n > data::uint160::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint16> nb (n);
        data::uint160 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (5)), u.words ().begin ());
        return u;
    }

    data::int160 cast_natural_to_int160 (const data::N &n) {
        if (n > data::int160::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint16> nb (n);
        data::int160 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (5)), u.words ().begin ());
        return u;
    }

    data::uint160_little cast_natural_to_uint160_little (const data::N &n) {
        if (n > data::uint160::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::uint160_little u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (20)), u.words ().begin ());
        return u;
    }

    data::int160_little cast_natural_to_int160_little (const data::N &n) {
        if (n > data::int160::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::int160_little u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (20)), u.words ().begin ());
        return u;
    }

    data::uint160_big cast_natural_to_uint160_big (const data::N &n) {
        if (n > data::uint160::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::uint160_big u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (20)), u.words ().begin ());
        return u;
    }

    data::int160_big cast_natural_to_int160_big (const data::N &n) {
        if (n > data::int160::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::int160_big u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (20)), u.words ().begin ());
        return u;
    }

    static_assert (std::same_as<data::uint256, data::math::uint<data::endian::little, 8, data::uint32>>);

    data::uint256 cast_natural_to_uint256 (const data::N &n) {
        if (n > data::uint256::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb {n};
        data::uint256 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (8)), u.words ().begin ());
        return u;
    }

    data::int256 cast_natural_to_int256 (const data::N &n) {
        if (n > data::int256::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::int256 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (8)), u.words ().begin ());
        return u;
    }

    data::uint256_little cast_natural_to_uint256_little (const data::N &n) {
        if (n > data::uint256::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::uint256_little u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (32)), u.words ().begin ());
        return u;
    }

    data::int256_little cast_natural_to_int256_little (const data::N &n) {
        if (n > data::int256::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::int256_little u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (32)), u.words ().begin ());
        return u;
    }

    data::uint256_big cast_natural_to_uint256_big (const data::N &n) {
        if (n > data::uint256::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::uint256_big u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (32)), u.words ().begin ());
        return u;
    }

    data::int256_big cast_natural_to_int256_big (const data::N &n) {
        if (n > data::int256::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::int256_big u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (32)), u.words ().begin ());
        return u;
    }

    static_assert (std::same_as<data::uint512, data::math::uint<data::endian::little, 16, data::uint32>>);

    data::uint512 cast_natural_to_uint512 (const data::N &n) {
        if (n > data::uint512::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::uint512 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (16)), u.words ().begin ());
        return u;
    }

    data::int512 cast_natural_to_int512 (const data::N &n) {
        if (n > data::int512::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::uint32> nb (n);
        data::int512 u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (16)), u.words ().begin ());
        return u;
    }

    data::uint512_little cast_natural_to_uint512_little (const data::N &n) {
        if (n > data::uint512::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::uint512_little u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (64)), u.words ().begin ());
        return u;
    }

    data::int512_little cast_natural_to_int512_little (const data::N &n) {
        if (n > data::uint512::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::int512_little u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (64)), u.words ().begin ());
        return u;
    }

    data::uint512_big cast_natural_to_uint512_big (const data::N &n) {
        if (n > data::int512::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::uint512_big u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (64)), u.words ().begin ());
        return u;
    }

    data::int512_big cast_natural_to_int512_big (const data::N &n) {
        if (n > data::int512::max ()) throw std::out_of_range {""};
        data::math::N_bytes<data::endian::little, data::byte> nb (n);
        data::int512_big u {};
        std::copy (nb.begin (), nb.begin () + std::min (nb.size (), size_t (64)), u.words ().begin ());
        return u;
    }
/*
    data::byte cast_integer_to_byte (const data::Z &n) {
        if (n > std::numeric_limits<data::byte>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int8 cast_integer_to_int8 (const data::Z &n) {
        if (n > std::numeric_limits<data::int8>::max () ||
            n < std::numeric_limits<data::int8>::min ()) throw std::out_of_range {""};

    }

    data::uint16 cast_integer_to_uint16 (const data::Z &n) {
        if (n > std::numeric_limits<data::uint16>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int16 cast_integer_to_int16 (const data::Z &n) {

    }

    data::uint16_little cast_integer_to_uint16_little (const data::Z &n) {
        if (n > std::numeric_limits<data::uint16>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int16_little cast_integer_to_int16_little (const data::Z &n) {

    }

    data::uint16_big cast_integer_to_uint16_big (const data::Z &n) {
        if (n > std::numeric_limits<data::uint16>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int16_big cast_integer_to_int16_big (const data::Z &n) {

    }

    data::uint32 cast_integer_to_uint32 (const data::Z &n) {
        if (n > std::numeric_limits<data::uint32>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int32 cast_integer_to_int32 (const data::Z &n) {

    }

    data::uint32_little cast_integer_to_uint32_little (const data::Z &n) {
        if (n > std::numeric_limits<data::uint32>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int32_little cast_integer_to_int32_little (const data::Z &n) {

    }

    data::uint32_big cast_integer_to_uint32_big (const data::Z &n) {
        if (n > std::numeric_limits<data::uint32>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int32_big cast_integer_to_int32_big (const data::Z &n) {

    }

    data::uint64 cast_integer_to_uint64 (const data::Z &n) {
        if (n > std::numeric_limits<data::uint64>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int64 cast_integer_to_int64 (const data::Z &n) {

    }

    data::uint64_little cast_integer_to_uint64_little (const data::Z &n) {
        if (n > std::numeric_limits<data::uint64>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int64_little cast_integer_to_int64_little (const data::Z &n) {

    }

    data::uint64_big cast_integer_to_uint64_big (const data::Z &n) {
        if (n > std::numeric_limits<data::uint64>::max () || n < 0) throw std::out_of_range {""};

    }

    data::int64_big cast_integer_to_int64_big (const data::Z &n) {

    }

    data::uint128 cast_integer_to_uint128 (const data::Z &n) {

    }

    data::int128 cast_integer_to_int128 (const data::Z &n) {

    }

    data::uint128_little cast_integer_to_uint128_little (const data::Z &n) {

    }

    data::int128_little cast_integer_to_int128_little (const data::Z &n) {

    }

    data::uint128_big cast_integer_to_uint128_big (const data::Z &n) {

    }

    data::int128_big cast_integer_to_int128_big (const data::Z &n) {

    }

    data::uint160 cast_integer_to_uint160 (const data::Z &n) {

    }

    data::int160 cast_integer_to_int160 (const data::Z &n) {

    }

    data::uint160_little cast_integer_to_uint160_little (const data::Z &n) {

    }

    data::int160_little cast_integer_to_int160_little (const data::Z &n) {

    }

    data::uint160_big cast_integer_to_uint160_big (const data::Z &n) {

    }

    data::int160_big cast_integer_to_int160_big (const data::Z &n) {

    }

    data::uint256 cast_integer_to_uint256 (const data::Z &n) {

    }

    data::int256 cast_integer_to_int256 (const data::Z &n) {

    }

    data::uint256_little cast_integer_to_uint256_little (const data::Z &n) {

    }

    data::int256_little cast_integer_to_int256_little (const data::Z &n) {

    }

    data::uint256_big cast_integer_to_uint256_big (const data::Z &n) {

    }

    data::int256_big cast_integer_to_int256_big (const data::Z &n) {

    }

    data::uint512 cast_integer_to_uint512 (const data::Z &n) {

    }

    data::int512 cast_integer_to_int512 (const data::Z &n) {

    }

    data::uint512_little cast_integer_to_uint512_little (const data::Z &n) {

    }

    data::int512_little cast_integer_to_int512_little (const data::Z &n) {

    }

    data::uint512_big cast_integer_to_uint512_big (const data::Z &n) {

    }

    data::int512_big cast_integer_to_int512_big (const data::Z &n) {

    }*/
}
