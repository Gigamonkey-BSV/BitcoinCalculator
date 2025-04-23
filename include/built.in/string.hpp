#ifndef BITCOIN_CALCULATOR_BUILTIN_STRING
#define BITCOIN_CALCULATOR_BUILTIN_STRING

#include <built.in/modular.hpp>

namespace Diophant {


    // string operations
    data::string string_cat (const data::string &x, const data::string &y);
    data::string string_left (const data::string &x, const Bitcoin::integer &y);
    data::string string_left (const data::string &x, const uint256 &y);
    data::string string_right (const data::string &x, const Bitcoin::integer &y);
    data::string string_right (const data::string &x, const uint256 &y);

    std::tuple<data::string, data::string> string_split (const data::string &x, const Bitcoin::integer &y);
    std::tuple<data::string, data::string> string_split (const data::string &x, const uint256 &y);

    bool string_equal (const data::string &x, const data::string &y);
    bool string_unequal (const data::string &x, const data::string &y);

    // size operations
    data::N string_size (const data::string &x);

}

#endif
