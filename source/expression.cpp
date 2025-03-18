#include <value.hpp>
#include <nodes.hpp>

namespace Diophant {

    bool operator == (Expression A, Expression B) {
        const node *a = A.get ();
        const node *b = B.get ();

        if (a == b) return true;


        throw data::exception {} << "incomplete method: << expression == expressions";
    }

    std::ostream &write_binary (std::ostream &, binary_operation, precedence Prec);
    std::ostream &write_unary (std::ostream &, unary_operation, precedence Prec);
    std::ostream &write_call (std::ostream &, call, precedence Prec);

    std::ostream &write (std::ostream &o, const node *n, precedence Prec) {
        if (n == nullptr) return o << "Nil";

        if (const value *v = dynamic_cast<const value *> (n); v != nullptr)
            return v->write (o);

        if (const symbol *x = dynamic_cast<const symbol *> (n); x != nullptr)
            return o << static_cast<const std::string &> (*x);

        if (const call *c = dynamic_cast<const call *> (n); c != nullptr) {
            precedence prec = precedence::call;
            if (Prec < prec) return write_call (o << "(", *c, prec) << ")";
            return write_call (o, *c, prec);
        }

        if (const unary_operation *u = dynamic_cast<const unary_operation *> (n); u != nullptr) {
            precedence prec = precedence::unary;
            if (Prec < prec) return write_unary (o << "(", *u, prec) << ")";
            return write_unary (o, *u, prec);
        }

        if (const binary_operation *b = dynamic_cast<const binary_operation *> (n); b != nullptr) {
            precedence prec = b->Operator;
            if (Prec < prec) return write_binary (o << "(", *b, prec) << ")";
            return write_binary (o, *b, prec);
        }

        throw data::exception {} <<
            "incomplete method: << expression; expression.cpp.";
    }

    std::ostream &operator << (std::ostream &o, Expression E) {
        return write (o, E.get (), max_precedence);
    }

    std::ostream &write_binary (std::ostream &, binary_operation, precedence Prec) {
        throw data::exception {} << "incomplete method: write_binary";
    }

    std::ostream &write_unary (std::ostream &, unary_operation, precedence Prec) {
        throw data::exception {} << "incomplete method: write_unary";
    }

    std::ostream &write_call (std::ostream &, call, precedence Prec) {
        throw data::exception {} << "incomplete method: write_call";
    }

}
