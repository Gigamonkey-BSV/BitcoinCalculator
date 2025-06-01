#ifndef BITCOIN_CALCULATOR_BUILTIN_NUMBERS
#define BITCOIN_CALCULATOR_BUILTIN_NUMBERS

#include <data/numbers.hpp>
#include <data/math.hpp>

namespace Diophant {

    // bit operations
    data::byte uint8_bit_not (data::byte x);
    data::byte uint8_bit_and (data::byte x, data::byte y);
    data::byte uint8_bit_xor (data::byte x, data::byte y);
    data::byte uint8_bit_or (data::byte x, data::byte y);
    data::byte uint8_bit_implies (data::byte x, data::byte y);
    data::byte uint8_bit_nand (data::byte x, data::byte y);
    data::byte uint8_bit_nor (data::byte x, data::byte y);

    data::int8 int8_bit_not (data::int8 x);
    data::int8 int8_bit_and (data::int8 x, data::int8 y);
    data::int8 int8_bit_xor (data::int8 x, data::int8 y);
    data::int8 int8_bit_or (data::int8 x, data::int8 y);
    data::int8 int8_bit_implies (data::int8 x, data::int8 y);
    data::int8 int8_bit_nand (data::int8 x, data::int8 y);
    data::int8 int8_bit_nor (data::int8 x, data::int8 y);

    data::uint16 uint16_bit_not (data::uint16 x);
    data::uint16 uint16_bit_and (data::uint16 x, data::uint16 y);
    data::uint16 uint16_bit_xor (data::uint16 x, data::uint16 y);
    data::uint16 uint16_bit_or (data::uint16 x, data::uint16 y);

    data::int16 int16_bit_not (data::int16 x);
    data::int16 int16_bit_and (data::int16 x, data::int16 y);
    data::int16 int16_bit_xor (data::int16 x, data::int16 y);
    data::int16 int16_bit_or (data::int16 x, data::int16 y);

    data::uint16_little uint16_little_bit_not (data::uint16_little x);
    data::uint16_little uint16_little_bit_and (data::uint16_little x, data::uint16_little y);
    data::uint16_little uint16_little_bit_xor (data::uint16_little x, data::uint16_little y);
    data::uint16_little uint16_little_bit_or (data::uint16_little x, data::uint16_little y);

    data::int16_little int16_little_bit_not (data::int16_little x);
    data::int16_little int16_little_bit_and (data::int16_little x, data::int16_little y);
    data::int16_little int16_little_bit_xor (data::int16_little x, data::int16_little y);
    data::int16_little int16_little_bit_or (data::int16_little x, data::int16_little y);

    data::uint16_big uint16_big_bit_not (data::uint16_big x);
    data::uint16_big uint16_big_bit_and (data::uint16_big x, data::uint16_big y);
    data::uint16_big uint16_big_bit_xor (data::uint16_big x, data::uint16_big y);
    data::uint16_big uint16_big_bit_or (data::uint16_big x, data::uint16_big y);

    data::int16_big int16_big_bit_not (data::int16_big x);
    data::int16_big int16_big_bit_and (data::int16_big x, data::int16_big y);
    data::int16_big int16_big_bit_xor (data::int16_big x, data::int16_big y);
    data::int16_big int16_big_bit_or (data::int16_big x, data::int16_big y);

    data::uint32 uint32_bit_not (data::uint32 x);
    data::uint32 uint32_bit_and (data::uint32 x, data::uint32 y);
    data::uint32 uint32_bit_xor (data::uint32 x, data::uint32 y);
    data::uint32 uint32_bit_or (data::uint32 x, data::uint32 y);

    data::int32 int32_bit_not (data::int32 x);
    data::int32 int32_bit_and (data::int32 x, data::int32 y);
    data::int32 int32_bit_xor (data::int32 x, data::int32 y);
    data::int32 int32_bit_or (data::int32 x, data::int32 y);

    data::uint32_little uint32_little_bit_not (data::uint32_little x);
    data::uint32_little uint32_little_bit_and (data::uint32_little x, data::uint32_little y);
    data::uint32_little uint32_little_bit_xor (data::uint32_little x, data::uint32_little y);
    data::uint32_little uint32_little_bit_or (data::uint32_little x, data::uint32_little y);

    data::int32_little int32_little_bit_not (data::int32_little x);
    data::int32_little int32_little_bit_and (data::int32_little x, data::int32_little y);
    data::int32_little int32_little_bit_xor (data::int32_little x, data::int32_little y);
    data::int32_little int32_little_bit_or (data::int32_little x, data::int32_little y);

    data::uint32_big uint32_big_bit_not (data::uint32_big x);
    data::uint32_big uint32_big_bit_and (data::uint32_big x, data::uint32_big y);
    data::uint32_big uint32_big_bit_xor (data::uint32_big x, data::uint32_big y);
    data::uint32_big uint32_big_bit_or (data::uint32_big x, data::uint32_big y);

    data::int32_big int32_big_bit_not (data::int32_big x);
    data::int32_big int32_big_bit_and (data::int32_big x, data::int32_big y);
    data::int32_big int32_big_bit_xor (data::int32_big x, data::int32_big y);
    data::int32_big int32_big_bit_or (data::int32_big x, data::int32_big y);

    data::uint64 uint64_bit_not (data::uint64 x);
    data::uint64 uint64_bit_and (data::uint64 x, data::uint64 y);
    data::uint64 uint64_bit_xor (data::uint64 x, data::uint64 y);
    data::uint64 uint64_bit_or (data::uint64 x, data::uint64 y);

    data::int64 int64_bit_not (data::int64 x);
    data::int64 int64_bit_and (data::int64 x, data::int64 y);
    data::int64 int64_bit_xor (data::int64 x, data::int64 y);
    data::int64 int64_bit_or (data::int64 x, data::int64 y);

    data::uint64_little uint64_little_bit_not (data::uint64_little x);
    data::uint64_little uint64_little_bit_and (data::uint64_little x, data::uint64_little y);
    data::uint64_little uint64_little_bit_xor (data::uint64_little x, data::uint64_little y);
    data::uint64_little uint64_little_bit_or (data::uint64_little x, data::uint64_little y);

    data::int64_little int64_little_bit_not (data::int64_little x);
    data::int64_little int64_little_bit_and (data::int64_little x, data::int64_little y);
    data::int64_little int64_little_bit_xor (data::int64_little x, data::int64_little y);
    data::int64_little int64_little_bit_or (data::int64_little x, data::int64_little y);

    data::uint64_big uint64_big_bit_not (data::uint64_big x);
    data::uint64_big uint64_big_bit_and (data::uint64_big x, data::uint64_big y);
    data::uint64_big uint64_big_bit_xor (data::uint64_big x, data::uint64_big y);
    data::uint64_big uint64_big_bit_or (data::uint64_big x, data::uint64_big y);

    data::int64_big int64_big_bit_not (data::int64_big x);
    data::int64_big int64_big_bit_and (data::int64_big x, data::int64_big y);
    data::int64_big int64_big_bit_xor (data::int64_big x, data::int64_big y);
    data::int64_big int64_big_bit_or (data::int64_big x, data::int64_big y);

    data::uint160 uint160_bit_not (const data::uint160 &x);
    data::uint160 uint160_bit_and (const data::uint160 &x, const data::uint160 &y);
    data::uint160 uint160_bit_xor (const data::uint160 &x, const data::uint160 &y);
    data::uint160 uint160_bit_or (const data::uint160 &x, const data::uint160 &y);

    data::int160 int160_bit_not (const data::int160 &x);
    data::int160 int160_bit_and (const data::int160 &x, const data::int160 &y);
    data::int160 int160_bit_xor (const data::int160 &x, const data::int160 &y);
    data::int160 int160_bit_or (const data::int160 &x, const data::int160 &y);

    data::uint160_little uint160_little_bit_not (const data::uint160_little &x);
    data::uint160_little uint160_little_bit_and (const data::uint160_little &x, const data::uint160_little &y);
    data::uint160_little uint160_little_bit_xor (const data::uint160_little &x, const data::uint160_little &y);
    data::uint160_little uint160_little_bit_or (const data::uint160_little &x, const data::uint160_little &y);

    data::int160_little int160_little_bit_not (const data::int160_little &x);
    data::int160_little int160_little_bit_and (const data::int160_little &x, const data::int160_little &y);
    data::int160_little int160_little_bit_xor (const data::int160_little &x, const data::int160_little &y);
    data::int160_little int160_little_bit_or (const data::int160_little &x, const data::int160_little &y);

    data::uint160_big uint160_big_bit_not (const data::uint160_big &x);
    data::uint160_big uint160_big_bit_and (const data::uint160_big &x, const data::uint160_big &y);
    data::uint160_big uint160_big_bit_xor (const data::uint160_big &x, const data::uint160_big &y);
    data::uint160_big uint160_big_bit_or (const data::uint160_big &x, const data::uint160_big &y);

    data::int160_big int160_big_bit_not (const data::int160_big &x);
    data::int160_big int160_big_bit_and (const data::int160_big &x, const data::int160_big &y);
    data::int160_big int160_big_bit_xor (const data::int160_big &x, const data::int160_big &y);
    data::int160_big int160_big_bit_or (const data::int160_big &x, const data::int160_big &y);

    data::uint256 uint256_bit_not (const data::uint256 &x);
    data::uint256 uint256_bit_and (const data::uint256 &x, const data::uint256 &y);
    data::uint256 uint256_bit_xor (const data::uint256 &x, const data::uint256 &y);
    data::uint256 uint256_bit_or (const data::uint256 &x, const data::uint256 &y);

    data::int256 int256_bit_not (const data::int256 &x);
    data::int256 int256_bit_and (const data::int256 &x, const data::int256 &y);
    data::int256 int256_bit_xor (const data::int256 &x, const data::int256 &y);
    data::int256 int256_bit_or (const data::int256 &x, const data::int256 &y);

    data::uint256_little uint256_little_bit_not (const data::uint256_little &x);
    data::uint256_little uint256_little_bit_and (const data::uint256_little &x, const data::uint256_little &y);
    data::uint256_little uint256_little_bit_xor (const data::uint256_little &x, const data::uint256_little &y);
    data::uint256_little uint256_little_bit_or (const data::uint256_little &x, const data::uint256_little &y);

    data::int256_little int256_little_bit_not (const data::int256_little &x);
    data::int256_little int256_little_bit_and (const data::int256_little &x, const data::int256_little &y);
    data::int256_little int256_little_bit_xor (const data::int256_little &x, const data::int256_little &y);
    data::int256_little int256_little_bit_or (const data::int256_little &x, const data::int256_little &y);

    data::uint256_big uint256_big_bit_not (const data::uint256_big &x);
    data::uint256_big uint256_big_bit_and (const data::uint256_big &x, const data::uint256_big &y);
    data::uint256_big uint256_big_bit_xor (const data::uint256_big &x, const data::uint256_big &y);
    data::uint256_big uint256_big_bit_or (const data::uint256_big &x, const data::uint256_big &y);

    data::int256_big int256_big_bit_not (const data::int256_big &x);
    data::int256_big int256_big_bit_and (const data::int256_big &x, const data::int256_big &y);
    data::int256_big int256_big_bit_xor (const data::int256_big &x, const data::int256_big &y);
    data::int256_big int256_big_bit_or (const data::int256_big &x, const data::int256_big &y);

    data::uint512 uint512_bit_not (const data::uint512 &x);
    data::uint512 uint512_bit_and (const data::uint512 &x, const data::uint512 &y);
    data::uint512 uint512_bit_xor (const data::uint512 &x, const data::uint512 &y);
    data::uint512 uint512_bit_or (const data::uint512 &x, const data::uint512 &y);

    data::int512 int512_bit_not (const data::int512 &x);
    data::int512 int512_bit_and (const data::int512 &x, const data::int512 &y);
    data::int512 int512_bit_xor (const data::int512 &x, const data::int512 &y);
    data::int512 int512_bit_or (const data::int512 &x, const data::int512 &y);

    data::uint512_little uint512_little_bit_not (const data::uint512_little &x);
    data::uint512_little uint512_little_bit_and (const data::uint512_little &x, const data::uint512_little &y);
    data::uint512_little uint512_little_bit_xor (const data::uint512_little &x, const data::uint512_little &y);
    data::uint512_little uint512_little_bit_or (const data::uint512_little &x, const data::uint512_little &y);

    data::int512_little int512_little_bit_not (const data::int512_little &x);
    data::int512_little int512_little_bit_and (const data::int512_little &x, const data::int512_little &y);
    data::int512_little int512_little_bit_xor (const data::int512_little &x, const data::int512_little &y);
    data::int512_little int512_little_bit_or (const data::int512_little &x, const data::int512_little &y);

    data::uint512_big uint512_big_bit_not (const data::uint512_big &x);
    data::uint512_big uint512_big_bit_and (const data::uint512_big &x, const data::uint512_big &y);
    data::uint512_big uint512_big_bit_xor (const data::uint512_big &x, const data::uint512_big &y);
    data::uint512_big uint512_big_bit_or (const data::uint512_big &x, const data::uint512_big &y);

    data::int512_big int512_big_bit_not (const data::int512_big &x);
    data::int512_big int512_big_bit_and (const data::int512_big &x, const data::int512_big &y);
    data::int512_big int512_big_bit_xor (const data::int512_big &x, const data::int512_big &y);
    data::int512_big int512_big_bit_or (const data::int512_big &x, const data::int512_big &y);

    // here we cannot support operations that negate bits because
    // all bits set all the way up to infinity is not a valid value.
    data::N natural_bit_and (const data::N x, const data::N y);
    data::N natural_bit_or (const data::N x, const data::N y);

    data::Z integer_bit_and (const data::Z x, const data::Z y);
    data::Z integer_bit_or (const data::Z x, const data::Z y);

    data::N_bytes_little N_bytes_bit_and (const data::N_bytes_little &x, const data::N_bytes_little &y);
    data::N_bytes_little N_bytes_bit_or (const data::N_bytes_little &x, const data::N_bytes_little &y);

    data::Z_bytes_little Z_bytes_bit_and (const data::Z_bytes_little &x, const data::Z_bytes_little &y);
    data::Z_bytes_little Z_bytes_bit_or (const data::Z_bytes_little &x, const data::Z_bytes_little &y);

    data::N_bytes_big N_bytes_bit_and (const data::N_bytes_big &x, const data::N_bytes_big &y);
    data::N_bytes_big N_bytes_bit_or (const data::N_bytes_big &x, const data::N_bytes_big &y);

    data::Z_bytes_big Z_bytes_bit_and (const data::Z_bytes_big &x, const data::Z_bytes_big &y);
    data::Z_bytes_big Z_bytes_bit_or (const data::Z_bytes_big &x, const data::Z_bytes_big &y);

    // comparisons
    bool natural_equal (const data::N x, const data::N y);
    bool natural_unequal (const data::N x, const data::N y);
    bool natural_greater_equal (const data::N x, const data::N y);
    bool natural_less_equal (const data::N x, const data::N y);
    bool natural_greater (const data::N x, const data::N y);
    bool natural_less (const data::N x, const data::N y);

    bool integer_equal (const data::Z x, const data::Z y);
    bool integer_unequal (const data::Z x, const data::Z y);
    bool integer_greater_equal (const data::Z x, const data::Z y);
    bool integer_less_equal (const data::Z x, const data::Z y);
    bool integer_greater (const data::Z x, const data::Z y);
    bool integer_less (const data::Z x, const data::Z y);

    bool N_bytes_equal (const data::N_bytes_little &x, const data::N_bytes_little &y);
    bool N_bytes_unequal (const data::N_bytes_little &x, const data::N_bytes_little &y);
    bool N_bytes_greater_equal (const data::N_bytes_little &x, const data::N_bytes_little &y);
    bool N_bytes_less_equal (const data::N_bytes_little &x, const data::N_bytes_little &y);
    bool N_bytes_greater (const data::N_bytes_little &x, const data::N_bytes_little &y);
    bool N_bytes_less (const data::N_bytes_little &x, const data::N_bytes_little &y);

    bool N_bytes_equal (const data::N_bytes_big & x, const data::N_bytes_big & y);
    bool N_bytes_unequal (const data::N_bytes_big & x, const data::N_bytes_big & y);
    bool N_bytes_greater_equal (const data::N_bytes_big & x, const data::N_bytes_big & y);
    bool N_bytes_less_equal (const data::N_bytes_big & x, const data::N_bytes_big & y);
    bool N_bytes_greater (const data::N_bytes_big & x, const data::N_bytes_big & y);
    bool N_bytes_less (const data::N_bytes_big & x, const data::N_bytes_big & y);

    bool Z_bytes_equal (const data::Z_bytes_little & x, const data::Z_bytes_little & y);
    bool Z_bytes_unequal (const data::Z_bytes_little & x, const data::Z_bytes_little & y);
    bool Z_bytes_greater_equal (const data::Z_bytes_little & x, const data::Z_bytes_little & y);
    bool Z_bytes_less_equal (const data::Z_bytes_little & x, const data::Z_bytes_little & y);
    bool Z_bytes_greater (const data::Z_bytes_little & x, const data::Z_bytes_little & y);
    bool Z_bytes_less (const data::Z_bytes_little & x, const data::Z_bytes_little & y);

    bool Z_bytes_equal (const data::Z_bytes_big & x, const data::Z_bytes_big & y);
    bool Z_bytes_unequal (const data::Z_bytes_big & x, const data::Z_bytes_big & y);
    bool Z_bytes_greater_equal (const data::Z_bytes_big & x, const data::Z_bytes_big & y);
    bool Z_bytes_less_equal (const data::Z_bytes_big & x, const data::Z_bytes_big & y);
    bool Z_bytes_greater (const data::Z_bytes_big & x, const data::Z_bytes_big & y);
    bool Z_bytes_less (const data::Z_bytes_big & x, const data::Z_bytes_big & y);

    bool uint8_equal (data::byte x, data::byte y);
    bool uint8_unequal (data::byte x, data::byte y);
    bool uint8_greater_equal (data::byte x, data::byte y);
    bool uint8_less_equal (data::byte x, data::byte y);
    bool uint8_greater (data::byte x, data::byte y);
    bool uint8_less (data::byte x, data::byte y);

    bool int8_equal (data::int8 x, data::int8 y);
    bool int8_unequal (data::int8 x, data::int8 y);
    bool int8_greater_equal (data::int8 x, data::int8 y);
    bool int8_less_equal (data::int8 x, data::int8 y);
    bool int8_greater (data::int8 x, data::int8 y);
    bool int8_less (data::int8 x, data::int8 y);

    bool uint16_equal (data::uint16 x, data::uint16 y);
    bool uint16_unequal (data::uint16 x, data::uint16 y);
    bool uint16_greater_equal (data::uint16 x, data::uint16 y);
    bool uint16_less_equal (data::uint16 x, data::uint16 y);
    bool uint16_greater (data::uint16 x, data::uint16 y);
    bool uint16_less (data::uint16 x, data::uint16 y);

    bool int16_equal (data::int16 x, data::int16 y);
    bool int16_unequal (data::int16 x, data::int16 y);
    bool int16_greater_equal (data::int16 x, data::int16 y);
    bool int16_less_equal (data::int16 x, data::int16 y);
    bool int16_greater (data::int16 x, data::int16 y);
    bool int16_less (data::int16 x, data::int16 y);

    bool uint16_little_equal (data::uint16_little x, data::uint16_little y);
    bool uint16_little_unequal (data::uint16_little x, data::uint16_little y);
    bool uint16_little_greater_equal (data::uint16_little x, data::uint16_little y);
    bool uint16_little_less_equal (data::uint16_little x, data::uint16_little y);
    bool uint16_little_greater (data::uint16_little x, data::uint16_little y);
    bool uint16_little_less (data::uint16_little x, data::uint16_little y);

    bool int16_little_equal (data::int16_little x, data::int16_little y);
    bool int16_little_unequal (data::int16_little x, data::int16_little y);
    bool int16_little_greater_equal (data::int16_little x, data::int16_little y);
    bool int16_little_less_equal (data::int16_little x, data::int16_little y);
    bool int16_little_greater (data::int16_little x, data::int16_little y);
    bool int16_little_less (data::int16_little x, data::int16_little y);

    bool uint16_big_equal (data::uint16_big x, data::uint16_big y);
    bool uint16_big_unequal (data::uint16_big x, data::uint16_big y);
    bool uint16_big_greater_equal (data::uint16_big x, data::uint16_big y);
    bool uint16_big_less_equal (data::uint16_big x, data::uint16_big y);
    bool uint16_big_greater (data::uint16_big x, data::uint16_big y);
    bool uint16_big_less (data::uint16_big x, data::uint16_big y);

    bool int16_big_equal (data::int16_big x, data::int16_big y);
    bool int16_big_unequal (data::int16_big x, data::int16_big y);
    bool int16_big_greater_equal (data::int16_big x, data::int16_big y);
    bool int16_big_less_equal (data::int16_big x, data::int16_big y);
    bool int16_big_greater (data::int16_big x, data::int16_big y);
    bool int16_big_less (data::int16_big x, data::int16_big y);

    bool uint32_equal (data::uint32 x, data::uint32 y);
    bool uint32_unequal (data::uint32 x, data::uint32 y);
    bool uint32_greater_equal (data::uint32 x, data::uint32 y);
    bool uint32_less_equal (data::uint32 x, data::uint32 y);
    bool uint32_greater (data::uint32 x, data::uint32 y);
    bool uint32_less (data::uint32 x, data::uint32 y);

    bool int32_equal (data::int32 x, data::int32 y);
    bool int32_unequal (data::int32 x, data::int32 y);
    bool int32_greater_equal (data::int32 x, data::int32 y);
    bool int32_less_equal (data::int32 x, data::int32 y);
    bool int32_greater (data::int32 x, data::int32 y);
    bool int32_less (data::int32 x, data::int32 y);

    bool uint32_little_equal (data::uint32_little x, data::uint32_little y);
    bool uint32_little_unequal (data::uint32_little x, data::uint32_little y);
    bool uint32_little_greater_equal (data::uint32_little x, data::uint32_little y);
    bool uint32_little_less_equal (data::uint32_little x, data::uint32_little y);
    bool uint32_little_greater (data::uint32_little x, data::uint32_little y);
    bool uint32_little_less (data::uint32_little x, data::uint32_little y);

    bool int32_little_equal (data::int32_little x, data::int32_little y);
    bool int32_little_unequal (data::int32_little x, data::int32_little y);
    bool int32_little_greater_equal (data::int32_little x, data::int32_little y);
    bool int32_little_less_equal (data::int32_little x, data::int32_little y);
    bool int32_little_greater (data::int32_little x, data::int32_little y);
    bool int32_little_less (data::int32_little x, data::int32_little y);

    bool uint32_big_equal (data::uint32_big x, data::uint32_big y);
    bool uint32_big_unequal (data::uint32_big x, data::uint32_big y);
    bool uint32_big_greater_equal (data::uint32_big x, data::uint32_big y);
    bool uint32_big_less_equal (data::uint32_big x, data::uint32_big y);
    bool uint32_big_greater (data::uint32_big x, data::uint32_big y);
    bool uint32_big_less (data::uint32_big x, data::uint32_big y);

    bool int32_big_equal (data::int32_big x, data::int32_big y);
    bool int32_big_unequal (data::int32_big x, data::int32_big y);
    bool int32_big_greater_equal (data::int32_big x, data::int32_big y);
    bool int32_big_less_equal (data::int32_big x, data::int32_big y);
    bool int32_big_greater (data::int32_big x, data::int32_big y);
    bool int32_big_less (data::int32_big x, data::int32_big y);

    bool uint64_equal (data::uint64 x, data::uint64 y);
    bool uint64_unequal (data::uint64 x, data::uint64 y);
    bool uint64_greater_equal (data::uint64 x, data::uint64 y);
    bool uint64_less_equal (data::uint64 x, data::uint64 y);
    bool uint64_greater (data::uint64 x, data::uint64 y);
    bool uint64_less (data::uint64 x, data::uint64 y);

    bool int64_equal (data::int64 x, data::int64 y);
    bool int64_unequal (data::int64 x, data::int64 y);
    bool int64_greater_equal (data::int64 x, data::int64 y);
    bool int64_less_equal (data::int64 x, data::int64 y);
    bool int64_greater (data::int64 x, data::int64 y);
    bool int64_less (data::int64 x, data::int64 y);

    bool uint64_little_equal (data::uint64_little x, data::uint64_little y);
    bool uint64_little_unequal (data::uint64_little x, data::uint64_little y);
    bool uint64_little_greater_equal (data::uint64_little x, data::uint64_little y);
    bool uint64_little_less_equal (data::uint64_little x, data::uint64_little y);
    bool uint64_little_greater (data::uint64_little x, data::uint64_little y);
    bool uint64_little_less (data::uint64_little x, data::uint64_little y);

    bool int64_little_equal (data::int64_little x, data::int64_little y);
    bool int64_little_unequal (data::int64_little x, data::int64_little y);
    bool int64_little_greater_equal (data::int64_little x, data::int64_little y);
    bool int64_little_less_equal (data::int64_little x, data::int64_little y);
    bool int64_little_greater (data::int64_little x, data::int64_little y);
    bool int64_little_less (data::int64_little x, data::int64_little y);

    bool uint64_big_equal (data::uint64_big x, data::uint64_big y);
    bool uint64_big_unequal (data::uint64_big x, data::uint64_big y);
    bool uint64_big_greater_equal (data::uint64_big x, data::uint64_big y);
    bool uint64_big_less_equal (data::uint64_big x, data::uint64_big y);
    bool uint64_big_greater (data::uint64_big x, data::uint64_big y);
    bool uint64_big_less (data::uint64_big x, data::uint64_big y);

    bool int64_big_equal (data::int64_big x, data::int64_big y);
    bool int64_big_unequal (data::int64_big x, data::int64_big y);
    bool int64_big_greater_equal (data::int64_big x, data::int64_big y);
    bool int64_big_less_equal (data::int64_big x, data::int64_big y);
    bool int64_big_greater (data::int64_big x, data::int64_big y);
    bool int64_big_less (data::int64_big x, data::int64_big y);

    bool uint128_equal (const data::uint128 &x, const data::uint128 &y);
    bool uint128_unequal (const data::uint128 &x, const data::uint128 &y);
    bool uint128_greater_equal (const data::uint128 &x, const data::uint128 &y);
    bool uint128_less_equal (const data::uint128 &x, const data::uint128 &y);
    bool uint128_greater (const data::uint128 &x, const data::uint128 &y);
    bool uint128_less (const data::uint128 &x, const data::uint128 &y);

    bool int128_equal (const data::int128 &x, const data::int128 &y);
    bool int128_unequal (const data::int128 &x, const data::int128 &y);
    bool int128_greater_equal (const data::int128 &x, const data::int128 &y);
    bool int128_less_equal (const data::int128 &x, const data::int128 &y);
    bool int128_greater (const data::int128 &x, const data::int128 &y);
    bool int128_less (const data::int128 &x, const data::int128 &y);

    bool uint128_little_equal (const data::uint128_little &x, const data::uint128_little &y);
    bool uint128_little_unequal (const data::uint128_little &x, const data::uint128_little &y);
    bool uint128_little_greater_equal (const data::uint128_little &x, const data::uint128_little &y);
    bool uint128_little_less_equal (const data::uint128_little &x, const data::uint128_little &y);
    bool uint128_little_greater (const data::uint128_little &x, const data::uint128_little &y);
    bool uint128_little_less (const data::uint128_little &x, const data::uint128_little &y);

    bool int128_little_equal (const data::int128_little &x, const data::int128_little &y);
    bool int128_little_unequal (const data::int128_little &x, const data::int128_little &y);
    bool int128_little_greater_equal (const data::int128_little &x, const data::int128_little &y);
    bool int128_little_less_equal (const data::int128_little &x, const data::int128_little &y);
    bool int128_little_greater (const data::int128_little &x, const data::int128_little &y);
    bool int128_little_less (const data::int128_little &x, const data::int128_little &y);

    bool uint128_big_equal (const data::uint128_big &x, const data::uint128_big &y);
    bool uint128_big_unequal (const data::uint128_big &x, const data::uint128_big &y);
    bool uint128_big_greater_equal (const data::uint128_big &x, const data::uint128_big &y);
    bool uint128_big_less_equal (const data::uint128_big &x, const data::uint128_big &y);
    bool uint128_big_greater (const data::uint128_big &x, const data::uint128_big &y);
    bool uint128_big_less (const data::uint128_big &x, const data::uint128_big &y);

    bool int128_big_equal (const data::int128_big &x, const data::int128_big &y);
    bool int128_big_unequal (const data::int128_big &x, const data::int128_big &y);
    bool int128_big_greater_equal (const data::int128_big &x, const data::int128_big &y);
    bool int128_big_less_equal (const data::int128_big &x, const data::int128_big &y);
    bool int128_big_greater (const data::int128_big &x, const data::int128_big &y);
    bool int128_big_less (const data::int128_big &x, const data::int128_big &y);

    bool uint160_equal (const data::uint160 &x, const data::uint160 &y);
    bool uint160_unequal (const data::uint160 &x, const data::uint160 &y);
    bool uint160_greater_equal (const data::uint160 &x, const data::uint160 &y);
    bool uint160_less_equal (const data::uint160 &x, const data::uint160 &y);
    bool uint160_greater (const data::uint160 &x, const data::uint160 &y);
    bool uint160_less (const data::uint160 &x, const data::uint160 &y);

    bool int160_equal (const data::int160 &x, const data::int160 &y);
    bool int160_unequal (const data::int160 &x, const data::int160 &y);
    bool int160_greater_equal (const data::int160 &x, const data::int160 &y);
    bool int160_less_equal (const data::int160 &x, const data::int160 &y);
    bool int160_greater (const data::int160 &x, const data::int160 &y);
    bool int160_less (const data::int160 &x, const data::int160 &y);

    bool uint160_little_equal (const data::uint160_little &x, const data::uint160_little &y);
    bool uint160_little_unequal (const data::uint160_little &x, const data::uint160_little &y);
    bool uint160_little_greater_equal (const data::uint160_little &x, const data::uint160_little &y);
    bool uint160_little_less_equal (const data::uint160_little &x, const data::uint160_little &y);
    bool uint160_little_greater (const data::uint160_little &x, const data::uint160_little &y);
    bool uint160_little_less (const data::uint160_little &x, const data::uint160_little &y);

    bool int160_little_equal (const data::int160_little &x, const data::int160_little &y);
    bool int160_little_unequal (const data::int160_little &x, const data::int160_little &y);
    bool int160_little_greater_equal (const data::int160_little &x, const data::int160_little &y);
    bool int160_little_less_equal (const data::int160_little &x, const data::int160_little &y);
    bool int160_little_greater (const data::int160_little &x, const data::int160_little &y);
    bool int160_little_less (const data::int160_little &x, const data::int160_little &y);

    bool uint160_big_equal (const data::uint160_big &x, const data::uint160_big &y);
    bool uint160_big_unequal (const data::uint160_big &x, const data::uint160_big &y);
    bool uint160_big_greater_equal (const data::uint160_big &x, const data::uint160_big &y);
    bool uint160_big_less_equal (const data::uint160_big &x, const data::uint160_big &y);
    bool uint160_big_greater (const data::uint160_big &x, const data::uint160_big &y);
    bool uint160_big_less (const data::uint160_big &x, const data::uint160_big &y);

    bool int160_big_equal (const data::int160_big &x, const data::int160_big &y);
    bool int160_big_unequal (const data::int160_big &x, const data::int160_big &y);
    bool int160_big_greater_equal (const data::int160_big &x, const data::int160_big &y);
    bool int160_big_less_equal (const data::int160_big &x, const data::int160_big &y);
    bool int160_big_greater (const data::int160_big &x, const data::int160_big &y);
    bool int160_big_less (const data::int160_big &x, const data::int160_big &y);

    bool uint256_equal (const data::uint256 &x, const data::uint256 &y);
    bool uint256_unequal (const data::uint256 &x, const data::uint256 &y);
    bool uint256_greater_equal (const data::uint256 &x, const data::uint256 &y);
    bool uint256_less_equal (const data::uint256 &x, const data::uint256 &y);
    bool uint256_greater (const data::uint256 &x, const data::uint256 &y);
    bool uint256_less (const data::uint256 &x, const data::uint256 &y);

    bool int256_equal (const data::int256 &x, const data::int256 &y);
    bool int256_unequal (const data::int256 &x, const data::int256 &y);
    bool int256_greater_equal (const data::int256 &x, const data::int256 &y);
    bool int256_less_equal (const data::int256 &x, const data::int256 &y);
    bool int256_greater (const data::int256 &x, const data::int256 &y);
    bool int256_less (const data::int256 &x, const data::int256 &y);

    bool uint256_little_equal (const data::uint256_little &x, const data::uint256_little &y);
    bool uint256_little_unequal (const data::uint256_little &x, const data::uint256_little &y);
    bool uint256_little_greater_equal (const data::uint256_little &x, const data::uint256_little &y);
    bool uint256_little_less_equal (const data::uint256_little &x, const data::uint256_little &y);
    bool uint256_little_greater (const data::uint256_little &x, const data::uint256_little &y);
    bool uint256_little_less (const data::uint256_little &x, const data::uint256_little &y);

    bool int256_little_equal (const data::int256_little &x, const data::int256_little &y);
    bool int256_little_unequal (const data::int256_little &x, const data::int256_little &y);
    bool int256_little_greater_equal (const data::int256_little &x, const data::int256_little &y);
    bool int256_little_less_equal (const data::int256_little &x, const data::int256_little &y);
    bool int256_little_greater (const data::int256_little &x, const data::int256_little &y);
    bool int256_little_less (const data::int256_little &x, const data::int256_little &y);

    bool uint256_big_equal (const data::uint256_big &x, const data::uint256_big &y);
    bool uint256_big_unequal (const data::uint256_big &x, const data::uint256_big &y);
    bool uint256_big_greater_equal (const data::uint256_big &x, const data::uint256_big &y);
    bool uint256_big_less_equal (const data::uint256_big &x, const data::uint256_big &y);
    bool uint256_big_greater (const data::uint256_big &x, const data::uint256_big &y);
    bool uint256_big_less (const data::uint256_big &x, const data::uint256_big &y);

    bool int256_big_equal (const data::int256_big &x, const data::int256_big &y);
    bool int256_big_unequal (const data::int256_big &x, const data::int256_big &y);
    bool int256_big_greater_equal (const data::int256_big &x, const data::int256_big &y);
    bool int256_big_less_equal (const data::int256_big &x, const data::int256_big &y);
    bool int256_big_greater (const data::int256_big &x, const data::int256_big &y);
    bool int256_big_less (const data::int256_big &x, const data::int256_big &y);

    bool uint512_equal (const data::uint512 &x, const data::uint512 &y);
    bool uint512_unequal (const data::uint512 &x, const data::uint512 &y);
    bool uint512_greater_equal (const data::uint512 &x, const data::uint512 &y);
    bool uint512_less_equal (const data::uint512 &x, const data::uint512 &y);
    bool uint512_greater (const data::uint512 &x, const data::uint512 &y);
    bool uint512_less (const data::uint512 &x, const data::uint512 &y);

    bool int512_equal (const data::int512 &x, const data::int512 &y);
    bool int512_unequal (const data::int512 &x, const data::int512 &y);
    bool int512_greater_equal (const data::int512 &x, const data::int512 &y);
    bool int512_less_equal (const data::int512 &x, const data::int512 &y);
    bool int512_greater (const data::int512 &x, const data::int512 &y);
    bool int512_less (const data::int512 &x, const data::int512 &y);

    bool uint512_little_equal (const data::uint512_little &x, const data::uint512_little &y);
    bool uint512_little_unequal (const data::uint512_little &x, const data::uint512_little &y);
    bool uint512_little_greater_equal (const data::uint512_little &x, const data::uint512_little &y);
    bool uint512_little_less_equal (const data::uint512_little &x, const data::uint512_little &y);
    bool uint512_little_greater (const data::uint512_little &x, const data::uint512_little &y);
    bool uint512_little_less (const data::uint512_little &x, const data::uint512_little &y);

    bool int512_little_equal (const data::int512_little &x, const data::int512_little &y);
    bool int512_little_unequal (const data::int512_little &x, const data::int512_little &y);
    bool int512_little_greater_equal (const data::int512_little &x, const data::int512_little &y);
    bool int512_little_less_equal (const data::int512_little &x, const data::int512_little &y);
    bool int512_little_greater (const data::int512_little &x, const data::int512_little &y);
    bool int512_little_less (const data::int512_little &x, const data::int512_little &y);

    bool uint512_big_equal (const data::uint512_big &x, const data::uint512_big &y);
    bool uint512_big_unequal (const data::uint512_big &x, const data::uint512_big &y);
    bool uint512_big_greater_equal (const data::uint512_big &x, const data::uint512_big &y);
    bool uint512_big_less_equal (const data::uint512_big &x, const data::uint512_big &y);
    bool uint512_big_greater (const data::uint512_big &x, const data::uint512_big &y);
    bool uint512_big_less (const data::uint512_big &x, const data::uint512_big &y);

    bool int512_big_equal (const data::int512_big &x, const data::int512_big &y);
    bool int512_big_unequal (const data::int512_big &x, const data::int512_big &y);
    bool int512_big_greater_equal (const data::int512_big &x, const data::int512_big &y);
    bool int512_big_less_equal (const data::int512_big &x, const data::int512_big &y);
    bool int512_big_greater (const data::int512_big &x, const data::int512_big &y);
    bool int512_big_less (const data::int512_big &x, const data::int512_big &y);

    // casts
    data::byte cast_natural_to_byte (const data::N);
    data::int8 cast_natural_to_int8 (const data::N);
    data::uint16 cast_natural_to_uint16 (const data::N);
    data::int16 cast_natural_to_int16 (const data::N);
    data::uint16_little cast_natural_to_uint16_little (const data::N);
    data::int16_little cast_natural_to_int16_little (const data::N);
    data::uint16_big cast_natural_to_uint16_big (const data::N);
    data::int16_big cast_natural_to_int16_big (const data::N);
    data::uint32 cast_natural_to_uint32 (const data::N);
    data::int32 cast_natural_to_int32 (const data::N);
    data::uint32_little cast_natural_to_uint32_little (const data::N);
    data::int32_little cast_natural_to_int32_little (const data::N);
    data::uint32_big cast_natural_to_uint32_big (const data::N);
    data::int32_big cast_natural_to_int32_big (const data::N);
    data::uint64 cast_natural_to_uint64 (const data::N);
    data::int64 cast_natural_to_int64 (const data::N);
    data::uint64_little cast_natural_to_uint64_little (const data::N);
    data::int64_little cast_natural_to_int64_little (const data::N);
    data::uint64_big cast_natural_to_uint64_big (const data::N);
    data::int64_big cast_natural_to_int64_big (const data::N);
    data::uint128 cast_natural_to_uint128 (const data::N);
    data::int128 cast_natural_to_int128 (const data::N);
    data::uint128_little cast_natural_to_uint128_little (const data::N);
    data::int128_little cast_natural_to_int128_little (const data::N);
    data::uint128_big cast_natural_to_uint128_big (const data::N);
    data::int128_big cast_natural_to_int128_big (const data::N);
    data::uint160 cast_natural_to_uint160 (const data::N);
    data::int160 cast_natural_to_int160 (const data::N);
    data::uint160_little cast_natural_to_uint160_little (const data::N);
    data::int160_little cast_natural_to_int160_little (const data::N);
    data::uint160_big cast_natural_to_uint160_big (const data::N);
    data::int160_big cast_natural_to_int160_big (const data::N);
    data::uint256 cast_natural_to_uint256 (const data::N);
    data::int256 cast_natural_to_int256 (const data::N);
    data::uint256_little cast_natural_to_uint256_little (const data::N);
    data::int256_little cast_natural_to_int256_little (const data::N);
    data::uint256_big cast_natural_to_uint256_big (const data::N);
    data::int256_big cast_natural_to_int256_big (const data::N);
    data::uint512 cast_natural_to_uint512 (const data::N);
    data::int512 cast_natural_to_int512 (const data::N);
    data::uint512_little cast_natural_to_uint512_little (const data::N);
    data::int512_little cast_natural_to_int512_little (const data::N);
    data::uint512_big cast_natural_to_uint512_big (const data::N);
    data::int512_big cast_natural_to_int512_big (const data::N);

    data::byte cast_integer_to_byte (const data::Z);
    data::int8 cast_integer_to_int8 (const data::Z);
    data::uint16 cast_integer_to_uint16 (const data::Z);
    data::int16 cast_integer_to_int16 (const data::Z);
    data::uint16_little cast_integer_to_uint16_little (const data::Z);
    data::int16_little cast_integer_to_int16_little (const data::Z);
    data::uint16_big cast_integer_to_uint16_big (const data::Z);
    data::int16_big cast_integer_to_int16_big (const data::Z);
    data::uint32 cast_integer_to_uint32 (const data::Z);
    data::int32 cast_integer_to_int32 (const data::Z);
    data::uint32_little cast_integer_to_uint32_little (const data::Z);
    data::int32_little cast_integer_to_int32_little (const data::Z);
    data::uint32_big cast_integer_to_uint32_big (const data::Z);
    data::int32_big cast_integer_to_int32_big (const data::Z);
    data::uint64 cast_integer_to_uint64 (const data::Z);
    data::int64 cast_integer_to_int64 (const data::Z);
    data::uint64_little cast_integer_to_uint64_little (const data::Z);
    data::int64_little cast_integer_to_int64_little (const data::Z);
    data::uint64_big cast_integer_to_uint64_big (const data::Z);
    data::int64_big cast_integer_to_int64_big (const data::Z);
    data::uint128 cast_integer_to_uint128 (const data::Z);
    data::int128 cast_integer_to_int128 (const data::Z);
    data::uint128_little cast_integer_to_uint128_little (const data::Z);
    data::int128_little cast_integer_to_int128_little (const data::Z);
    data::uint128_big cast_integer_to_uint128_big (const data::Z);
    data::int128_big cast_integer_to_int128_big (const data::Z);
    data::uint160 cast_integer_to_uint160 (const data::Z);
    data::int160 cast_integer_to_int160 (const data::Z);
    data::uint160_little cast_integer_to_uint160_little (const data::Z);
    data::int160_little cast_integer_to_int160_little (const data::Z);
    data::uint160_big cast_integer_to_uint160_big (const data::Z);
    data::int160_big cast_integer_to_int160_big (const data::Z);
    data::uint256 cast_integer_to_uint256 (const data::Z);
    data::int256 cast_integer_to_int256 (const data::Z);
    data::uint256_little cast_integer_to_uint256_little (const data::Z);
    data::int256_little cast_integer_to_int256_little (const data::Z);
    data::uint256_big cast_integer_to_uint256_big (const data::Z);
    data::int256_big cast_integer_to_int256_big (const data::Z);
    data::uint512 cast_integer_to_uint512 (const data::Z);
    data::int512 cast_integer_to_int512 (const data::Z);
    data::uint512_little cast_integer_to_uint512_little (const data::Z);
    data::int512_little cast_integer_to_int512_little (const data::Z);
    data::uint512_big cast_integer_to_uint512_big (const data::Z);
    data::int512_big cast_integer_to_int512_big (const data::Z);

    data::byte harden (data::byte);

    data::uint16 harden (data::uint16);
    data::uint32 harden (data::uint32);
    data::uint64 harden (data::uint64);
    data::uint128 harden (const data::uint128 &);
    data::uint160 harden (const data::uint160 &);
    data::uint256 harden (const data::uint256 &);
    data::uint512 harden (const data::uint512 &);

    data::uint16_little harden_little (data::uint16_little);
    data::uint32_little harden_little (data::uint32_little);
    data::uint64_little harden_little (data::uint64_little);
    data::uint128_little harden_little (const data::uint128_little &);
    data::uint160_little harden_little (const data::uint160_little &);
    data::uint256_little harden_little (const data::uint256_little &);
    data::uint512_little harden_little (const data::uint512_little &);

    data::uint16_big harden_big (data::uint16_big);
    data::uint32_big harden_big (data::uint32_big);
    data::uint64_big harden_big (data::uint64_big);
    data::uint128_big harden_big (const data::uint128_big &);
    data::uint160_big harden_big (const data::uint160_big &);
    data::uint256_big harden_big (const data::uint256_big &);
    data::uint512_big harden_big (const data::uint512_big &);

    // negate and abs.
    data::Z natural_negate (const data::N &x);
    data::Z integer_negate (const data::Z &x);

    data::N integer_abs (const data::Z &x);

    data::byte uint8_negate (data::byte x);
    data::int8 int8_negate (data::int8 x);

    data::int8 int8_abs (data::int8 x);

    data::uint16 uint16_negate (data::uint16 x);
    data::int16 int16_negate (data::int16 x);

    data::int16 int16_abs (data::int16 x);

    data::uint32 uint32_negate (data::uint32 x);
    data::int32 int32_negate (data::int32 x);

    data::int32 int32_abs (data::int32 x);

    data::uint64 uint64_negate (data::uint64 x);
    data::int64 int64_negate (data::int64 x);

    data::int64 int64_abs (data::int64 x);

    data::uint16_little uint16_little_negate (data::uint16_little x);
    data::int16_little int16_little_negate (data::int16_little x);

    data::int16_little int16_little_abs (data::int16_little x);

    data::uint24_little uint24_little_negate (data::uint24_little x);
    data::int24_little int24_little_negate (data::int24_little x);

    data::int24_little int24_little_abs (data::int24_little x);

    data::uint32_little uint32_little_negate (data::uint32_little x);
    data::int32_little int32_little_negate (data::int32_little x);

    data::int32_little int32_little_abs (data::int32_little x);

    data::uint64_little uint64_little_negate (data::uint64_little x);
    data::int64_little int64_little_negate (data::int64_little x);

    data::int64_little int64_little_abs (data::int64_little x);

    data::uint16_big uint16_big_negate (data::uint16_big x);
    data::int16_big int16_big_negate (data::int16_big x);

    data::int16_big int16_big_abs (data::int16_big x);

    data::uint24_big uint24_big_negate (data::uint24_big x);
    data::int24_big int24_big_negate (data::int24_big x);

    data::int24_big int24_big_abs (data::int24_big x);

    data::uint32_big uint32_big_negate (data::uint32_big x);
    data::int32_big int32_big_negate (data::int32_big x);

    data::int32_big int32_big_abs (data::int32_big x);

    data::uint64_big uint64_big_negate (data::uint64_big x);
    data::int64_big int64_big_negate (data::int64_big x);

    data::int64_big int64_big_abs (data::int64_big x);

    // basic arithmetic
    data::N natural_plus (const data::N &x, const data::N &y);
    data::Z integer_plus (const data::Z &x, const data::Z &y);

    data::Z natural_minus (const data::N &x, const data::N &y);
    data::Z integer_minus (const data::Z &x, const data::Z &y);

    data::N natural_times (const data::N &x, const data::N &y);
    data::Z integer_times (const data::Z &x, const data::Z &y);

    data::N natural_mod (const data::N &x, const data::N &y);
    data::N integer_mod (const data::Z &x, const data::N &y);

    data::N natural_plus_mod (const data::N &x, const data::N &y, const data::N &z);
    data::N integer_plus_mod (const data::Z &x, const data::Z &y, const data::N &z);

    data::N natural_minus_mod (const data::N &x, const data::N &y, const data::N &z);
    data::N integer_minus_mod (const data::Z &x, const data::Z &y, const data::N &z);

    data::N natural_times_mod (const data::N &x, const data::N &y, const data::N &z);
    data::N integer_times_mod (const data::Z &x, const data::Z &y, const data::N &z);

    data::N natural_pow_mod (const data::N &x, const data::N &y, const data::N &z);
    data::N integer_pow_mod (const data::Z &x, const data::N &y, const data::N &z);

    data::N natural_power (const data::N &x, const data::N &y);
    data::Z integer_power (const data::Z &x, const data::N &y);

    data::Q natural_invert (const data::N &x);
    data::Q integer_invert (const data::Z &x);

    data::Q natural_power (const data::N &x, const data::Z &y);
    data::Q integer_power (const data::Z &x, const data::Z &y);

    std::tuple<data::N, data::N> natural_div_mod (const data::N &x, const data::N &y);
    std::tuple<data::Z, data::N> integer_div_mod (const data::Z &x, const data::Z &y);

    data::Q natural_divide (const data::N &x, const data::N &y);
    data::Q integer_divide (const data::Z &x, const data::Z &y);

    data::Q rational_abs (const data::Q &x);
    data::Q rational_negate (const data::Q &x);

    data::Q rational_plus (const data::Q &x, const data::Q &y);
    data::Q rational_minus (const data::Q &x, const data::Q &y);
    data::Q rational_times (const data::Q &x, const data::Q &y);
    data::Q rational_invert (const data::Q &x);
    data::Q rational_divide (const data::Q &x, const data::Q &y);
    data::Q rational_power (const data::Q, const data::Z &y);

}

#endif

