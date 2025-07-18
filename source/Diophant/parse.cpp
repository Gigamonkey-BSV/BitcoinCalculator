#include <Diophant/parse.hpp>
#include <Diophant/values/leaf.hpp>
#include <Diophant/values/lambda.hpp>
#include <Diophant/values/list.hpp>
#include <Diophant/values/struct.hpp>
#include <Diophant/operators.hpp>
#include <Diophant/grammar.hpp>

#include <gigamonkey/secp256k1.hpp>
#include <gigamonkey/numbers.hpp>
#include <data/io/wait_for_enter.hpp>

namespace tao_pegtl_grammar {
    struct read_definition : seq<ws, definition, ws, eof> {};
    struct read_declaration : seq<ws, declaration, ws, eof> {};
    struct read_expression : seq<opt<seq<ws, expression<atom>>>, ws, eof> {};
}

namespace Diophant {
    struct parser {
        program complete () const;

        void push (Expression);

        void call ();

        void open_list ();
        void close_list ();

        void open_struct ();
        void close_struct ();

        void read_symbol (const symbol &);

        void make_if ();

        void start_lambda ();
        void complete_lambda ();

        void let_open ();
        void let_close ();

        void unary (unary_operand op);
        void binary (binary_operand op);

        void declare ();
        void define ();

        bool valid ();

    private:

        data::stack<expression> Exp;
        data::stack<data::stack<expression>> Back;

        data::stack<data::stack<symbol>> Symbols;

        program Final;

    };

    struct number_parser {
        std::string Value {};
        data::maybe<std::string> Fixed {};
        bool UnsignedFlag {false};
        data::maybe<data::endian::order> Endian;
        expression result ();
    };

    namespace rules {
        namespace pegtl = tao::pegtl;

        template <typename Rule> struct read_number : pegtl::nothing<Rule> {};

        template <> struct read_number<tao_pegtl_grammar::number_lit> {
            template <typename Input>
            static void apply (const Input &in, number_parser &eval) {
                eval.Value = in.string ();
            }
        };

        template <> struct read_number<tao_pegtl_grammar::fixed_size_flag> {
            template <typename Input>
            static void apply (const Input &in, number_parser &eval) {
                eval.Fixed = in.string ();
            }
        };

        template <> struct read_number<tao_pegtl_grammar::unsigned_flag> {
            template <typename Input>
            static void apply (const Input &in, number_parser &eval) {
                eval.UnsignedFlag = true;
            }
        };

        template <> struct read_number<tao_pegtl_grammar::big_endian_flag> {
            template <typename Input>
            static void apply (const Input &in, number_parser &eval) {
                eval.Endian = data::endian::big;
            }
        };

        template <> struct read_number<tao_pegtl_grammar::little_endian_flag> {
            template <typename Input>
            static void apply (const Input &in, number_parser &eval) {
                eval.Endian = data::endian::little;
            }
        };

        template <typename Rule> struct read_expression : pegtl::nothing<Rule> {};

        template <> struct read_expression<tao_pegtl_grammar::number_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                tao::pegtl::memory_input<> num {in.string (), "expression"};
                number_parser p {};
                tao::pegtl::parse<tao_pegtl_grammar::number_lit, read_number> (num, p);
                eval.push (p.result ());
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::dec_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (natural::make (data::N {in.string_view ()}));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::hex_lit> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (call::make (symbol::make ("scriptnum"),
                    {bytes::make (Bitcoin::integer::read (in.string_view ()))}));
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
                // this must be valid because it woludn't be here if the parser didn't read it.
                eval.push (bytes::make (*data::encoding::hex::read (x.substr (1, x.size () - 2))));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::symbol> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (symbol::make (in.string ()));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::var> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (blank::make (in.string ().substr (1)));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::anon_var> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.push (blank::make (in.string ().substr (1)));
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::open_list> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.open_list ();
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::close_list> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.close_list ();
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::open_struct> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.open_struct ();
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::close_struct> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.close_struct ();
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::rule_symbol> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.read_symbol (in.string ());
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::lambda_open> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.start_lambda ();
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::lambda_symbol> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.read_symbol (in.string ());
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::classic_lambda<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.complete_lambda ();
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::compact_lambda<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                std::cout << " we don't know how to read compact lambdas yet" << std::endl;
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::dif<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.make_if ();
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::let_open> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.let_open ();
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::let<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.let_close ();
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::left_unary_operation<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                // NOTE this won't work if we ever have any unary operators that are bigger than one char.
                eval.unary (unary_operand {*in.begin ()});
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::call_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.call ();
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::dot_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::dot);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::cat_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::cat);
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

        template <typename atom> struct read_expression<tao_pegtl_grammar::identical_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::identical);
            }
        };

        template <typename atom> struct read_expression<tao_pegtl_grammar::apply_op<atom>> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::apply);
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

        template <> struct read_expression<tao_pegtl_grammar::such_that_op> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.binary (binary_operand::such_that);
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::clause> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.define ();
            }
        };

        template <> struct read_expression<tao_pegtl_grammar::declaration> {
            template <typename Input>
            static void apply (const Input &in, parser &eval) {
                eval.declare ();
            }
        };

    }

    template <typename expr>
    program read (const data::string &input) {
        parser p;
        tao::pegtl::memory_input<> in {input, "expression"};

        try {
            if (!tao::pegtl::parse<expr, rules::read_expression> (in, p)) {
                std::stringstream ss;
                ss << input;
                throw parse_error {ss.str ()};
            }
        } catch (tao::pegtl::parse_error &err) {
            const tao::pegtl::position &pos = err.positions ().front ();
            std::stringstream ss;
            ss << input << "; failure at column " << pos.column;
            throw parse_error {ss.str ()};
        }

        return p.complete ();
    }

    expression read_expression (const data::string &input) {
        return first (read<tao_pegtl_grammar::read_expression> (input)).Predicate;
    }

    statement read_definition (const data::string &input) {
        return first (read<tao_pegtl_grammar::read_definition> (input));
    }

    pattern read_declaration (const data::string &input) {
        return *first (read<tao_pegtl_grammar::read_declaration> (input)).Subject;
    }

    program read_line (const data::string &input) {
        return read<tao_pegtl_grammar::program> (input);
    }

    void inline parser::call () {
        if (size (Exp) < 2) throw data::exception {} << "invalid parser stack on call: too small";
        Exp = prepend (rest (rest (Exp)), call::make (first (rest (Exp)), {first (Exp)}));
    }

    void inline parser::push (Expression x) {
        Exp >>= x;
    }

    program inline parser::complete () const {

        if (Exp.size () > 1) throw data::exception {} << "parsing error: stack is " << Exp;

        if (Final.size () == 0) {
            if (Exp.size () == 0) return program {statement {nil::make ()}};
            return program {statement {first (Exp)}};
        }

        if (Exp.size () == 0) return reverse (Final);
        return reverse (Final >> statement {first (Exp)});
    }

    void parser::unary (unary_operand op) {
        Exp = prepend (rest (Exp), unop::make (op, first (Exp)));
    }

    void parser::binary (binary_operand op) {
        expression x = first (Exp);
        expression z = first (rest (Exp));
        if (is_associative (op)) {
            if (const auto *bb = dynamic_cast<const binop *> (x.get ()); bb != nullptr) {
                if (bb->Operand == op) {
                    Exp = prepend (rest (rest (Exp)), binop::make (op, prepend (bb->Body, z)));
                    return;
                }
            }
        }

        Exp = prepend (rest (rest (Exp)), binop::make (op, z, x));
    }

    void parser::open_list () {
        Back = prepend (Back, Exp);
        Exp = {};
    }

    void parser::close_list () {
        Exp = prepend (first (Back), list::make (reverse (Exp)));
        Back = rest (Back);
    }

    void parser::start_lambda () {
        open_list ();
        Symbols >>= data::stack<symbol> {};
    }

    void parser::complete_lambda () {

        // remove all previous expressions from the stack.
        // This is done in case we start to read one lambda
        // format and then find out that it isn't valid and
        // read the other one instead.
        Exp = prepend (first (Back), lambda::make (reverse (first (Symbols)), first (Exp)));
        Symbols = rest (Symbols);
        Back = rest (Back);
    }

    void parser::open_struct () {
        Back = prepend (Back, Exp);
        Exp = {};
        Symbols >>= data::stack<symbol> {};
    }

    void parser::close_struct () {
        Exp = prepend (first (Back), dstruct::make (reverse (data::map_thread ([] (const symbol &x, const expression &p) {
            return data::entry<symbol, expression> {x, p};
        }, first (Symbols), Exp))));
        Symbols = rest (Symbols);
        Back = rest (Back);
    }

    void parser::make_if () {
        Exp = prepend (drop (Exp, 3), dif::make (Exp[2], Exp[1], Exp[0]));
    }

    void parser::read_symbol (const symbol &x) {
        Symbols = prepend (rest (Symbols), first (Symbols) >> x);
    }

    void parser::let_open () {
        Back = prepend (Back, Exp);
        Exp = {};
        Symbols >>= data::stack<symbol> {};
    }

    void parser::let_close () {
        Exp = prepend (first (Back), let::make (reverse (data::map_thread ([] (const symbol &x, const expression &p) {
            return data::entry<const symbol, expression> {x, p};
        }, first (Symbols), rest (Exp))), first (Exp)));
        Symbols = rest (Symbols);
        Back = rest (Back);
    }

    // top entry on stack should be a declaration.
    void parser::declare () {
        Final >>= statement {pattern {first (Exp)}};
        Exp = rest (Exp);
    }

    void parser::define () {
        Final >>= statement {pattern {first (rest (Exp))}, first (Exp)};
        Exp = rest (rest (Exp));
    }

}
