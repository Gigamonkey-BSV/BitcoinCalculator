#include <Diophant/built.in/string.hpp>

namespace Diophant {

    bool string_equal (const data::string &x, const data::string &y) {
        return x == y;
    }

    bool string_unequal (const data::string &x, const data::string &y) {
        return x != y;
    }

    bool bytes_equal (const data::bytes &x, const data::bytes &y) {
        return x == y;
    }

    bool bytes_unequal (const data::bytes &x, const data::bytes &y) {
        return x != y;
    }

    data::byte bytes_get (const data::bytes &b, const data::N &n) {
        return b [data::uint64 (n)];
    }

    data::uint32 string_get (const data::string &b, const data::N &n) {
        return b [data::uint64 (n)];
    }

    data::byte bytes_get (const data::bytes &b, const Bitcoin::integer &n) {
        return b [data::int64 (n)];
    }

    data::uint32 string_get (const data::string &b, const Bitcoin::integer &n) {
        return b [data::int64 (n)];
    }

    data::N string_size (const data::string &x) {
        return x.size ();
    }

    data::N bytes_size (const data::bytes &b) {
        return b.size ();
    }

    data::string string_cat (const data::string &x, const data::string &y) {
        return Bitcoin::cat (x, y);
    }

    data::bytes bytes_cat (const data::bytes &x, const data::bytes &y) {
        return Bitcoin::cat (x, y);
    }

    data::string string_left (const data::string &x, const Bitcoin::integer &y) {
        return data::string {Bitcoin::left (x, size_t (y))};
    }

    data::string string_left (const data::string &x, const data::N &y) {
        return data::string {Bitcoin::left (x, size_t (y))};
    }

    data::string string_right (const data::string &x, const Bitcoin::integer &y) {
        return data::string {Bitcoin::right (x, size_t (y))};
    }

    data::string string_right (const data::string &x, const data::N &y) {
        return data::string {Bitcoin::right (x, size_t (y))};
    }

    data::bytes bytes_left (const data::bytes &x, const Bitcoin::integer &y) {
        return data::bytes {Bitcoin::left (x, size_t (y))};
    }

    data::bytes bytes_right (const data::bytes &x, const Bitcoin::integer &y) {
        return data::bytes {Bitcoin::right (x, size_t (y))};
    }

    data::bytes bytes_left (const data::bytes &x, const data::N &y) {
        return data::bytes {Bitcoin::left (x, size_t (y))};
    }

    data::bytes bytes_right (const data::bytes &x, const data::N &y) {
        return data::bytes {Bitcoin::right (x, size_t (y))};
    }

    std::tuple<data::string, data::string> string_split (const data::string &x, const Bitcoin::integer &y) {
        auto [first, second] = Bitcoin::split (x, size_t (y));
        return {data::string (first), data::string (second)};
    }

    std::tuple<data::string, data::string> string_split (const data::string &x, const data::N &y) {
        auto [first, second] = Bitcoin::split (x, size_t (y));
        return {data::string (first), data::string (second)};
    }

    std::tuple<data::bytes, data::bytes> bytes_split (const data::bytes &x, const Bitcoin::integer &y) {
        auto [first, second] = Bitcoin::split (x, size_t (y));
        return {data::bytes (first), data::bytes (second)};
    }

    std::tuple<data::bytes, data::bytes> bytes_split (const data::bytes &x, const data::N &y) {
        auto [first, second] = Bitcoin::split (x, size_t (y));
        return {data::bytes (first), data::bytes (second)};
    }

    data::bytes bytes_left_shift (const data::bytes &x, const Bitcoin::integer &y) {
        return Bitcoin::left_shift (x, size_t (y));
    }

    data::bytes bytes_right_shift (const data::bytes &x, const Bitcoin::integer &y) {
        return Bitcoin::right_shift (x, size_t (y));
    }

    data::bytes bytes_left_shift (const data::bytes &x, const data::N &y) {
        return Bitcoin::left_shift (x, size_t (y));
    }

    data::bytes bytes_right_shift (const data::bytes &x, const data::N &y) {
        return Bitcoin::right_shift (x, size_t (y));
    }

    data::byte get (data::uint16_little b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (data::int16_little b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (data::uint32_little b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (data::int32_little b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (data::uint64_little b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (data::int64_little b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (data::uint16_big b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (data::int16_big b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (data::uint32_big b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (data::int32_big b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (data::uint64_big b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (data::int64_big b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (data::uint16_little b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (data::int16_little b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (data::uint32_little b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (data::int32_little b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (data::uint64_little b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (data::int64_little b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (data::uint16_big b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (data::int16_big b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (data::uint32_big b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (data::int32_big b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (data::uint64_big b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (data::int64_big b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (const data::uint160_little & b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (const data::int160_little & b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (const data::uint160_big & b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (const data::int160_big & b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (const data::uint160_little & b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (const data::int160_little & b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (const data::uint160_big & b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (const data::int160_big & b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (const data::uint256_little & b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (const data::int256_little & b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (const data::uint256_big & b, const data::N & n) { return b[size_t (n)] ; }
    data::byte get (const data::int256_big & b, const data::N & n) { return b[size_t (n)] ; }

    data::byte get (const data::uint256_little & b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (const data::int256_little & b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

    data::byte get (const data::uint256_big & b, const Bitcoin::integer & n) { return b[size_t (n)] ; }
    data::byte get (const data::int256_big & b, const Bitcoin::integer & n) { return b[size_t (n)] ; }

}
