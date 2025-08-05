#ifndef BITCOIN_CALCULATOR_PARSE_ERROR
#define BITCOIN_CALCULATOR_PARSE_ERROR

#include <stdexcept>
#include <data/string.hpp>

namespace Diophant {

    struct parse_error : std::logic_error {
        parse_error (): std::logic_error {"could not parse input"} {};
        parse_error (const data::string &line):
            std::logic_error {std::string {} + "could not parse input: " + line} {};
    };

}

#endif

