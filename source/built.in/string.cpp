#include <built.in/string.hpp>

namespace Diophant {

    bool string_equal (const data::string &x, const data::string &y) {
        return x == y;
    }

    bool string_unequal (const data::string &x, const data::string &y) {
        return x != y;
    }

    data::string string_cat (const data::string &x, const data::string &y) {
        return Bitcoin::cat (x, y);
    }

    data::string string_left (const data::string &x, const Bitcoin::integer &y) {
        return data::string {Bitcoin::left (x, static_cast<size_t> (data::int64 (y)))};
    }

    data::string string_left (const data::string &x, const uint256 &y) {
        return data::string {Bitcoin::left (x, size_t (y))};
    }

    data::string string_right (const data::string &x, const Bitcoin::integer &y) {
        return data::string {Bitcoin::right (x, static_cast<size_t> (data::int64 (y)))};
    }

    data::string string_right (const data::string &x, const uint256 &y) {
        return data::string {Bitcoin::right (x, size_t (y))};
    }

    std::tuple<data::string, data::string> string_split (const data::string &x, const Bitcoin::integer &y) {
        auto sp = Bitcoin::split (x, static_cast<size_t> (data::int64 (y)));
        return {data::string (sp.first), data::string (sp.second)};
    }

    std::tuple<data::string, data::string> string_split (const data::string &x, const uint256 &y) {
        auto sp = Bitcoin::split (x, static_cast<size_t> (data::uint64 (y)));
        return {data::string (sp.first), data::string (sp.second)};
    }

}
