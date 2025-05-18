#ifndef BITCOIN_CALCULATOR_BUILTIN_STRING
#define BITCOIN_CALCULATOR_BUILTIN_STRING

#include <Diophant/built.in/numbers.hpp>
#include <Diophant/built.in/scriptnum.hpp>

namespace Diophant {

    bool string_equal (const data::string &x, const data::string &y);
    bool string_unequal (const data::string &x, const data::string &y);

    bool bytes_equal (const data::bytes &x, const data::bytes &y);
    bool bytes_unequal (const data::bytes &x, const data::bytes &y);

    data::byte bytes_get (const data::bytes &, const data::N &);
    data::uint32 string_get (const data::string &, const data::N &);

    data::byte bytes_get (const data::bytes &, const Bitcoin::integer &);
    data::uint32 string_get (const data::string &, const Bitcoin::integer &);

    data::bytes bytes_cat (const data::bytes &x, const data::bytes &y);
    data::string string_cat (const data::string &x, const data::string &y);

    // size operations
    data::N string_size (const data::string &x);
    data::N bytes_size (const data::bytes &b);

    data::string string_left (const data::string &x, const Bitcoin::integer &y);
    data::string string_left (const data::string &x, const data::N &y);
    data::string string_right (const data::string &x, const Bitcoin::integer &y);
    data::string string_right (const data::string &x, const data::N &y);

    std::tuple<data::string, data::string> string_split (const data::string &x, const Bitcoin::integer &y);
    std::tuple<data::string, data::string> string_split (const data::string &x, const data::N &y);

    data::bytes bytes_left (const data::bytes &x, const Bitcoin::integer &y);
    data::bytes bytes_left (const data::bytes &x, const data::N &y);
    data::bytes bytes_right (const data::bytes &x, const Bitcoin::integer &y);
    data::bytes bytes_right (const data::bytes &x, const data::N &y);

    std::tuple<data::bytes, data::bytes> bytes_split (const data::bytes &x, const Bitcoin::integer &y);
    std::tuple<data::bytes, data::bytes> bytes_split (const data::bytes &x, const data::N &y);

    data::bytes bytes_left_shift (const data::bytes &x, const Bitcoin::integer &y);
    data::bytes bytes_right_shift (const data::bytes &x, const Bitcoin::integer &y);

    data::bytes bytes_left_shift (const data::bytes &x, const data::N &y);
    data::bytes bytes_right_shift (const data::bytes &x, const data::N &y);

    data::bytes bitcoin_checksum (const data::bytes &x);

    // number types as strings.
    data::byte get (data::uint16_little, const data::N &);
    data::byte get (data::int16_little, const data::N &);

    data::byte get (data::uint32_little, const data::N &);
    data::byte get (data::int32_little, const data::N &);

    data::byte get (data::uint64_little, const data::N &);
    data::byte get (data::int64_little, const data::N &);

    data::byte get (data::uint16_big, const data::N &);
    data::byte get (data::int16_big, const data::N &);

    data::byte get (data::uint32_big, const data::N &);
    data::byte get (data::int32_big, const data::N &);

    data::byte get (data::uint64_big, const data::N &);
    data::byte get (data::int64_big, const data::N &);

    data::byte get (data::uint16_little, const Bitcoin::integer &);
    data::byte get (data::int16_little, const Bitcoin::integer &);

    data::byte get (data::uint32_little, const Bitcoin::integer &);
    data::byte get (data::int32_little, const Bitcoin::integer &);

    data::byte get (data::uint64_little, const Bitcoin::integer &);
    data::byte get (data::int64_little, const Bitcoin::integer &);

    data::byte get (data::uint16_big, const Bitcoin::integer &);
    data::byte get (data::int16_big, const Bitcoin::integer &);

    data::byte get (data::uint32_big, const Bitcoin::integer &);
    data::byte get (data::int32_big, const Bitcoin::integer &);

    data::byte get (data::uint64_big, const Bitcoin::integer &);
    data::byte get (data::int64_big, const Bitcoin::integer &);

    data::byte get (const data::uint160_little &, const data::N &);
    data::byte get (const data::int160_little &, const data::N &);

    data::byte get (const data::uint160_big &, const data::N &);
    data::byte get (const data::int160_big &, const data::N &);

    data::byte get (const data::uint160_little &, const Bitcoin::integer &);
    data::byte get (const data::int160_little &, const Bitcoin::integer &);

    data::byte get (const data::uint160_big &, const Bitcoin::integer &);
    data::byte get (const data::int160_big &, const Bitcoin::integer &);

    data::byte get (const data::uint256_little &, const data::N &);
    data::byte get (const data::int256_little &, const data::N &);

    data::byte get (const data::uint256_big &, const data::N &);
    data::byte get (const data::int256_big &, const data::N &);

    data::byte get (const data::uint256_little &, const Bitcoin::integer &);
    data::byte get (const data::int256_little &, const Bitcoin::integer &);

    data::byte get (const data::uint256_big &, const Bitcoin::integer &);
    data::byte get (const data::int256_big &, const Bitcoin::integer &);

}

#endif
