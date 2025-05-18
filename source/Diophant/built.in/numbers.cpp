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
        return x >= y;}

    bool uint32_big_less_equal (data::uint32_big x, data::uint32_big y) {return x <= y;}

    bool uint32_big_greater (data::uint32_big x, data::uint32_big y) {
        return x > y;}

    bool uint32_big_less (data::uint32_big x, data::uint32_big y) {return x < y;}

    bool int32_big_equal (data::int32_big x, data::int32_big y) {
        return x == y;}

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
}
