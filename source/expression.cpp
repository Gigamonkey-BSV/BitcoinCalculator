#include <values/list.hpp>
#include <nodes.hpp>
#include <pattern.hpp>

namespace Diophant {

    bool operator == (Expression A, Expression B) {

        const form *a = A.get ();
        const form *b = B.get ();

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
                b->Operator == c->Operator && b->Body == c->Body;
        }

        if (const list *ll = dynamic_cast<const list *> (a); ll != nullptr) {
            const list *mm = dynamic_cast<const list *> (b);
            return mm == nullptr ? false: ll->List == mm->List;
        }

        if (const call *fx = dynamic_cast<const call *> (a); fx != nullptr) {
            const call *gx = dynamic_cast<const call *> (b);
            if (gx == nullptr) return false;
            if (fx->Fun != gx->Fun) return false;
            return fx->Args == gx->Args;
        }

        throw data::exception {} << "incomplete method: expression == expressions; trying to evaluate " << A << " == " << B;
    }

    std::ostream &write_binary (std::ostream &, const binary_operation &);
    std::ostream &write_unary (std::ostream &, const unary_operation &);
    std::ostream &write_call (std::ostream &, const call &);

    std::ostream &write (std::ostream &o, const form *n, precedence Prec) {
        if (n == nullptr) return o << "undefined";

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

        if (const blank *bl = dynamic_cast<const blank *> (n); bl != nullptr)
            return o << "_" << bl->Name;

        if (const typed *y = dynamic_cast<const typed *> (n); y != nullptr)
            return o << y->Match << " : " << y->Required;

        throw data::exception {} << "incomplete method: << expression; expression.cpp.";
    }

    std::ostream &operator << (std::ostream &o, const form *n) {
        return write (o, n, max_precedence);
    }

    std::ostream &write_binary (std::ostream &o, const binary_operation &b) {
        data::stack<expression> body = b.Body;
        if (data::size (body) < 2) throw data::exception {} << "invalid binary operation " << b.Operator;

        write (o, body.first ().get (), b.Operator);
        body = data::rest (body);
        do {
            write (o << " " << b.Operator << " ", body.first ().get (), b.Operator);
            body = data::rest (body);
        } while (!data::empty (body));
        return o;
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
