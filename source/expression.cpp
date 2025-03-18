#include <value.hpp>
#include <nodes.hpp>

namespace Diophant {

    bool operator == (Expression A, Expression B) {
        const node *a = A.get ();
        const node *b = B.get ();

        if (a == b) return true;


        throw data::exception {} << "incomplete method: << expression == expressions";
    }

    std::ostream &write_binary (std::ostream &, binary_operation, binary_operand Precedence);
    std::ostream &write_unary (std::ostream &, unary_operation, binary_operand Precedence);
    std::ostream &write_call (std::ostream &, call, binary_operand Precedence);

    std::ostream &write (std::ostream &o, const node *n, binary_operand Precedence) {
        if (n == nullptr) return o << "Nil";

        if (const value *v = dynamic_cast<const value *> (n); v != nullptr)
            return v->write (o);

        if (const symbol *x = dynamic_cast<const symbol *> (n); x != nullptr)
            return o << static_cast<const std::string &> (*x);

        if (const call *c = dynamic_cast<const call *> (n); c != nullptr) {
            binary_operand precedence = binary_operand::call;
            if (Precedence < precedence) return write_call (o << "(", *c, precedence) << ")";
            return write_call (o, *c, precedence);
        }

        if (const unary_operation *u = dynamic_cast<const unary_operation *> (n); u != nullptr) {
            binary_operand precedence = binary_operand::unary;
            if (Precedence < precedence) return write_unary (o << "(", *u, precedence) << ")";
            return write_unary (o, *u, precedence);
        }

        if (const binary_operation *b = dynamic_cast<const binary_operation *> (n); b != nullptr) {
            binary_operand precedence = b->Operator;
            if (Precedence < precedence) return write_binary (o << "(", *b, precedence) << ")";
            return write_binary (o, *b, precedence);
        }

        throw data::exception {} <<
            "incomplete method: << expression; expression.cpp.";
    }

    std::ostream &operator << (std::ostream &o, Expression E) {
        return write (o, E.get (), max_precedence);
    }

}
