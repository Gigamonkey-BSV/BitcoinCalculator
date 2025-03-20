#include <values/list.hpp>
#include <nodes.hpp>

namespace Diophant {

    bool operator == (Expression A, Expression B) {
        const node *a = A.get ();
        const node *b = B.get ();

        if (a == b) return true;
        if (a == nullptr || b == nullptr) return false;

        if (const value *v = dynamic_cast<const value *> (a); v != nullptr) {
            const value *w = dynamic_cast<const value *> (b);
            if (w == nullptr) return false;
            return *v == *w;
        }

        if (const symbol *x = dynamic_cast<const symbol *> (a); x != nullptr) {
            const symbol *y = dynamic_cast<const symbol *> (b);
            if (y == nullptr) return false;
            return *x == *y;
        }

        if (const unary_operation *u = dynamic_cast<const unary_operation *> (a); u != nullptr) {
            const unary_operation *v = dynamic_cast<const unary_operation *> (b);
            return v == nullptr ? false: u->Operator == v->Operator && u->Body == v->Body;
        }

        if (const binary_operation *b = dynamic_cast<const binary_operation *> (a); b != nullptr) {
            const binary_operation *c = dynamic_cast<const binary_operation *> (b);
            return c == nullptr ? false:
                b->Operator == c->Operator && b->Left == c->Left && b->Right == c->Right;
        }

        if (const list *ll = dynamic_cast<const list *> (a); ll != nullptr) {
            const list *mm = dynamic_cast<const list *> (b);
            return mm == nullptr ? false: ll->List == mm->List;
        }

        throw data::exception {} << "incomplete method: expression == expressions; trying to evaluate " << A << " == " << B;
    }

    std::ostream &write_binary (std::ostream &, const binary_operation &);
    std::ostream &write_unary (std::ostream &, const unary_operation &);
    std::ostream &write_call (std::ostream &, const call &);

    std::ostream &write (std::ostream &o, const node *n, precedence Prec) {
        if (n == nullptr) return o << "nil";

        if (const value *v = dynamic_cast<const value *> (n); v != nullptr)
            return v->write (o);

        if (const symbol *x = dynamic_cast<const symbol *> (n); x != nullptr)
            return o << static_cast<const std::string &> (*x);

        if (const call *c = dynamic_cast<const call *> (n); c != nullptr) {
            if (Prec < precedence::call) return write_call (o << "(", *c) << ")";
            return write_call (o, *c);
        }

        if (const unary_operation *u = dynamic_cast<const unary_operation *> (n); u != nullptr) {
            if (Prec < precedence::unary) return write_unary (o << "(", *u) << ")";
            return write_unary (o, *u);
        }

        if (const binary_operation *b = dynamic_cast<const binary_operation *> (n); b != nullptr) {
            if (Prec < b->Operator) return write_binary (o << "(", *b) << ")";
            return write_binary (o, *b);
        }

        if (const list *ll = dynamic_cast<const list *> (n); ll != nullptr)
            return data::functional::write (o, ll->List);

        throw data::exception {} <<
            "incomplete method: << expression; expression.cpp.";
    }

    std::ostream &operator << (std::ostream &o, Expression E) {
        return write (o, E.get (), max_precedence);
    }

    std::ostream &write_binary (std::ostream &o, const binary_operation &b) {
        return write (write (o, b.Left.get (), b.Operator) << b.Operator, b.Right.get (), b.Operator);
    }

    std::ostream &write_unary (std::ostream &o, const unary_operation &u) {
        return write (o << u.Operator, u.Body.get (), precedence::unary);
    }

    std::ostream &write_call (std::ostream &o, const call &c) {
        write (o, c.Fun.get (), precedence::call);
        auto args = c.Args;
        while (!data::empty (args)) {
            write (o << " ", data::first (args).get (), precedence::call);
            args = data::rest (args);
        }
        return o;
    }

}
