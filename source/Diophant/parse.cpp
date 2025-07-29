#include <Diophant/parse.hpp>
#include <Diophant/parse/parser.hpp>
#include <Diophant/values/lambda.hpp>
#include <Diophant/values/list.hpp>
#include <Diophant/values/struct.hpp>
#include <Diophant/operators.hpp>

namespace Diophant {

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
