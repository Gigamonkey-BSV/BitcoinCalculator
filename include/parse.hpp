#ifndef BITCOIN_CALCULATOR_PARSE
#define BITCOIN_CALCULATOR_PARSE

#include <expression.hpp>

namespace Diophant {

    struct parse_error : std::logic_error {
        parse_error (): std::logic_error {"could not parse input"} {};
        parse_error (const data::string &line):
            std::logic_error {std::string {} + "could not parse input: " + line} {};
    };

    expression read_line (const data::string &in);

}

#endif

