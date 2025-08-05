#ifndef BITCOIN_CALCULATOR_PARSE
#define BITCOIN_CALCULATOR_PARSE

#include <Diophant/machine.hpp>
#include <Diophant/parse/error.hpp>

namespace Diophant {

    expression read_expression (const data::string &in);

    pattern read_declaration (const data::string &in);

    statement read_definition (const data::string &in);

    program read_line (const data::string &in);

}

#endif

