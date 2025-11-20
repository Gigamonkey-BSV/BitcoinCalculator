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
        if (b.size () == 0) throw data::exception {} << "cannot get " << n << "th index of empty string";
        return b [size_t (n % b.size ())];
    }

    data::uint32 string_get (const data::string &b, const data::N &n) {
        if (b.size () == 0) throw data::exception {} << "cannot get " << n << "th index of empty string";
        return b [size_t (n % b.size ())];
    }

    data::byte bytes_get (const data::bytes &b, const data::Z &n) {
        if (b.size () == 0) throw data::exception {} << "cannot get " << n << "th index of empty string";
        return b [size_t (n % b.size ())];
    }

    data::uint32 string_get (const data::string &b, const data::Z &n) {
        if (b.size () == 0) throw data::exception {} << "cannot get " << n << "th index of empty string";
        return b [size_t (n % b.size ())];
    }

    data::byte bytes_get (const data::bytes &b, const data::bytes &n) {
        if (b.size () == 0) throw data::exception {} << "cannot get " << n << "th index of empty string";
        return b [size_t (Bitcoin::integer {n} % b.size ())];
    }

    data::uint32 string_get (const data::string &b, const data::bytes &n) {
        if (b.size () == 0) throw data::exception {} << "cannot get " << n << "th index of empty string";
        return b [size_t (Bitcoin::integer {n} % b.size ())];
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

    data::string string_left (const data::string &x, const data::bytes &y) {
        if (x.size () == 0) {
            if (Bitcoin::integer {y} == 0) return data::string {};
            throw data::exception {} << "cannot take " << Bitcoin::integer {y} << " bytes from empty string";
        }
        return data::string {Bitcoin::left (x, size_t (Bitcoin::integer {y} % x.size ()))};
    }

    data::string string_left (const data::string &x, const data::N &y) {
        if (x.size () == 0) {
            if (y == 0) return data::string {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        return data::string {Bitcoin::left (x, size_t (y % x.size ()))};
    }

    data::string string_left (const data::string &x, const data::Z &y) {
        if (x.size () == 0) {
            if (Bitcoin::integer {y} == 0) return data::string {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        return data::string {Bitcoin::left (x, size_t (y % x.size ()))};
    }

    data::string string_right (const data::string &x, const data::bytes &y) {
        if (x.size () == 0) {
            if (Bitcoin::integer {y} == 0) return data::string {};
            throw data::exception {} << "cannot take " << Bitcoin::integer {y} << " bytes from empty string";
        }
        return data::string {Bitcoin::right (x, size_t (Bitcoin::integer {y} % x.size ()))};
    }

    data::string string_right (const data::string &x, const data::N &y) {
        if (x.size () == 0) {
            if (y == 0) return data::string {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        return data::string {Bitcoin::right (x, size_t (y % x.size ()))};
    }

    data::string string_right (const data::string &x, const data::Z &y) {
        if (x.size () == 0) {
            if (y == 0) return data::string {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        return data::string {Bitcoin::right (x, size_t (y % x.size ()))};
    }

    data::bytes bytes_left (const data::bytes &x, const data::bytes &y) {
        if (x.size () == 0) {
            if (Bitcoin::integer {y} == 0) return data::bytes {};
            throw data::exception {} << "cannot take " << Bitcoin::integer {y} << " bytes from empty string";
        }
        return data::bytes {Bitcoin::left (x, size_t (Bitcoin::integer {y} % x.size ()))};
    }

    data::bytes bytes_right (const data::bytes &x, const data::bytes &y) {
        if (x.size () == 0) {
            if (Bitcoin::integer {y} == 0) return data::bytes {};
            throw data::exception {} << "cannot take " << Bitcoin::integer {y} << " bytes from empty string";
        }
        return data::bytes {Bitcoin::right (x, size_t (Bitcoin::integer {y} % x.size ()))};
    }

    data::bytes bytes_left (const data::bytes &x, const data::N &y) {
        if (x.size () == 0) {
            if (y == 0) return data::bytes {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        return data::bytes {Bitcoin::left (x, size_t (y % x.size ()))};
    }

    data::bytes bytes_right (const data::bytes &x, const data::N &y) {
        if (x.size () == 0) {
            if (y == 0) return data::bytes {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        return data::bytes {Bitcoin::right (x, size_t (y % x.size ()))};
    }

    data::bytes bytes_left (const data::bytes &x, const data::Z &y) {
        if (x.size () == 0) {
            if (y == 0) return data::bytes {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        return data::bytes {Bitcoin::left (x, size_t (y % x.size ()))};
    }

    data::bytes bytes_right (const data::bytes &x, const data::Z &y) {
        if (x.size () == 0) {
            if (y == 0) return data::bytes {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        return data::bytes {Bitcoin::right (x, size_t (y % x.size ()))};
    }

    std::tuple<data::string, data::string> string_split (const data::string &x, const data::bytes &y) {
        if (x.size () == 0) {
            if (Bitcoin::integer {y} == 0) return std::tuple<data::string, data::string> {};
            throw data::exception {} << "cannot take " << Bitcoin::integer {y} << " bytes from empty string";
        }
        auto [first, second] = Bitcoin::split (x, size_t (Bitcoin::integer {y} % x.size ()));
        return {data::string (first), data::string (second)};
    }

    std::tuple<data::string, data::string> string_split (const data::string &x, const data::Z y) {
        if (x.size () == 0) {
            if (y == 0) return std::tuple<data::string, data::string> {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        auto [first, second] = Bitcoin::split (x, size_t (y % x.size ()));
        return {data::string (first), data::string (second)};
    }

    std::tuple<data::string, data::string> string_split (const data::string &x, const data::N y) {
        return string_split (x, data::Z (y));
    }

    std::tuple<data::bytes, data::bytes> bytes_split (const data::bytes &x, const data::bytes &y) {
        if (x.size () == 0) {
            if (Bitcoin::integer {y} == 0) return std::tuple<data::bytes, data::bytes> {};
            throw data::exception {} << "cannot take " << Bitcoin::integer {y} << " bytes from empty string";
        }
        auto [first, second] = Bitcoin::split (x, size_t (Bitcoin::integer {y} % x.size ()));
        return {data::bytes (first), data::bytes (second)};
    }

    std::tuple<data::bytes, data::bytes> bytes_split (const data::bytes &x, const data::N y) {
        return bytes_split (x, data::Z (y));
    }

    std::tuple<data::bytes, data::bytes> bytes_split (const data::bytes &x, const data::Z y) {
        if (x.size () == 0) {
            if (y == 0) return std::tuple<data::bytes, data::bytes> {};
            throw data::exception {} << "cannot take " << y << " bytes from empty string";
        }
        auto [first, second] = Bitcoin::split (x, size_t (y % x.size ()));
        return {data::bytes (first), data::bytes (second)};
    }

    data::bytes bytes_left_shift (const data::bytes &x, const data::bytes &y) {
        if (x.size () == 0) return data::bytes {};
        return Bitcoin::left_shift (x, size_t (Bitcoin::integer {y} % x.size ()));
    }

    data::bytes bytes_right_shift (const data::bytes &x, const data::bytes &y) {
        if (x.size () == 0) return data::bytes {};
        return Bitcoin::right_shift (x, size_t (Bitcoin::integer {y} % x.size ()));
    }

    data::bytes bytes_left_shift (const data::bytes &x, const data::N &y) {
        if (x.size () == 0) return data::bytes {};
        return Bitcoin::left_shift (x, size_t (y % x.size ()));
    }

    data::bytes bytes_right_shift (const data::bytes &x, const data::N &y) {
        if (x.size () == 0) return data::bytes {};
        return Bitcoin::right_shift (x, size_t (y % x.size ()));
    }

    data::bytes bytes_left_shift (const data::bytes &x, const data::Z &y) {
        if (x.size () == 0) return data::bytes {};
        return Bitcoin::left_shift (x, size_t (y % x.size ()));
    }

    data::bytes bytes_right_shift (const data::bytes &x, const data::Z &y) {
        if (x.size () == 0) return data::bytes {};
        return Bitcoin::right_shift (x, size_t (y % x.size ()));
    }

    data::string string_left_shift (const data::string &x, const data::bytes &y) {
        if (x.size () == 0) return data::string {};
        return Bitcoin::left_shift (x, size_t (Bitcoin::integer {y} % x.size ()));
    }

    data::string string_right_shift (const data::string &x, const data::bytes &y) {
        if (x.size () == 0) return data::string {};
        return Bitcoin::right_shift (x, size_t (Bitcoin::integer {y} % x.size ()));
    }

    data::string string_left_shift (const data::string &x, const data::N &y) {
        if (x.size () == 0) return data::string {};
        return Bitcoin::left_shift (x, size_t (y % x.size ()));
    }

    data::string string_right_shift (const data::string &x, const data::N &y) {
        if (x.size () == 0) return data::string {};
        return Bitcoin::right_shift (x, size_t (y % x.size ()));
    }

    data::string string_left_shift (const data::string &x, const data::Z &y) {
        if (x.size () == 0) return data::string {};
        return Bitcoin::left_shift (x, size_t (y % x.size ()));
    }

    data::string string_right_shift (const data::string &x, const data::Z &y) {
        if (x.size () == 0) return data::string {};
        return Bitcoin::right_shift (x, size_t (y % x.size ()));
    }

}
