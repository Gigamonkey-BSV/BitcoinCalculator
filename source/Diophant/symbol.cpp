
#include <Diophant/parse/parser.hpp>

namespace tao_pegtl_grammar {
    struct read_symbol : seq<symbol, eof> {};
}

namespace Diophant {
    
    bool symbol::valid () const {
        parser p;
        tao::pegtl::memory_input<> in {*this, "expression"};

        try {
            if (!tao::pegtl::parse<tao_pegtl_grammar::read_symbol, rules::read_expression> (in, p)) return false;
        } catch (tao::pegtl::parse_error &err) {
            return false;
        }

        return true;
    }
}