#include <parse.hpp>
#include <value.hpp>
#include <operators.hpp>
#include <parse/grammar.hpp>

#include <gigamonkey/secp256k1.hpp>
#include <gigamonkey/numbers.hpp>

namespace tao_pegtl_grammar {
    struct expression_grammar : must<seq<ws, expression, ws, eof>> {};
}

namespace Diophant {
    struct parser {
        void push (Expression);

        void call ();

        void unary (unary_operand op);
        void binary (binary_operand op);

        bool valid ();

        expression top ();

        data::stack<expression> Exp;

    };

    namespace rules {
        namespace pegtl = tao::pegtl;

        template <typename Rule> struct read_expression : pegtl::nothing<Rule> {};

        template <> struct read_expression<tao_pegtl_grammar::expression_atom> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                std::cout << "reading expression atom " << data::string {in.string ()} << std::endl;
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::dec_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (secret::make (secp256k1::secret {uint256 {in.string_view ()}}));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::hex_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (scriptnum::make (Bitcoin::integer {in.string_view ()}));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::pubkey_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (pubkey::make (Bitcoin::pubkey {in.string_view ()}));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::string_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                auto x = in.string_view ();
                eval.push (string::make (data::string {x.substr (1, x.size () - 2)}));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::hex_string_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                auto x = in.string_view ();
                eval.push (scriptnum::make (Bitcoin::integer {x.substr (1, x.size () - 2)}));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::symbol> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (symbol::make (in.string ()));
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::call<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.call ();
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::unary_operation<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                std::cout << "::: reading unary operation: " << data::string {in.string ()} << std::endl;
                // NOTE this won't work if we ever have any unary operators that are bigger than one char.
                eval.unary (unary_operand {*in.begin ()});
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::mul_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::times);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::pow_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::power);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::div_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::divide);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::div_mod_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::divmod);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::add_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::plus);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::sub_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::minus);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::greater_equal_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::greater_equal);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::less_equal_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::less_equal);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::less_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::less);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::greater_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::greater);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::bool_equal_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::bool_equal);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::bool_unequal_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::bool_unequal);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::bool_and_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::bool_and);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::bool_or_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::bool_or);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::equal_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::equal);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::unequal_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::unequal);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::intuitionistic_and_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::intuitionistic_and);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::intuitionistic_or_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::intuitionistic_or);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::intuitionistic_implies_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::intuitionistic_implies);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::element_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::element);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::such_that_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::such_that);
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::expression_grammar> {
            template <typename Input>
            static void apply (const Input &in, parser &eval);
        };

    }

    expression read_line (const std::string &input) {
        parser p;
        tao::pegtl::memory_input<> in {input, "expression"};

        try {
            if (!tao::pegtl::parse<tao_pegtl_grammar::expression, rules::read_expression> (in, p));
            throw parse_error {std::string {"could not parse line "} + input};
        } catch (tao::pegtl::parse_error &err) {
            const auto &pos = err.positions ().front ();
            std::stringstream ss;
            ss << "could not parse line: \"" << input << "\"; failure at column " << pos.column;
            throw parse_error {ss.str ()};
        }

        return p.top ();
    }

    void inline parser::call () {
        Exp = prepend (
            rest (rest (Exp)),
            call::make (
                first (rest (Exp)),
                take (Exp, 1)));
    }

    void inline parser::push (Expression x) {
        Exp <<= x;
    }

    expression inline parser::top () {
        if (Exp.size () == 0) return expression {};
        return Exp.first ();
    }

    void parser::unary (unary_operand op) {
        Exp = prepend (rest (Exp), unary_operation::make (op, first (Exp)));
    }

    void parser::binary (binary_operand op) {
        throw data::exception {} << "parser::binary incomplete";
    }

}
