#include <Diophant/values/list.hpp>
#include <Diophant/values/struct.hpp>
#include <Diophant/nodes.hpp>
#include <Diophant/pattern.hpp>
#include <Diophant/parse/parser.hpp>

namespace Diophant {

    expression::expression (const std::string &x) {
        *this = read_expression (x);
    }

    std::string write (Expression ex) {
        std::stringstream ss;
        ss << ex;
        return ss.str ();
    }

    bool operator == (Expression A, Expression B) {

        const form *a = A.get ();
        const form *b = B.get ();

        if (a == b) return true;
        if (a == nullptr || b == nullptr) return false;

        const node *n = dynamic_cast<const node *> (a);
        const node *m = dynamic_cast<const node *> (b);

        if (m == nullptr || n == nullptr) throw data::exception {} << "check equality of patterns";

        return *n == *m;
    }

    std::ostream &write_binary (std::ostream &, const binop &);
    std::ostream &write_unary (std::ostream &, const unop &);
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

        if (const unop *u = dynamic_cast<const unop *> (n); u != nullptr) {
            if (Prec < precedence::unary) return write_unary (o << "(", *u) << ")";
            return write_unary (o, *u);
        }

        if (const binop *b = dynamic_cast<const binop *> (n); b != nullptr) {
            if (Prec < b->Operand) return write_binary (o << "(", *b) << ")";
            return write_binary (o, *b);
        }

        if (const list *ll = dynamic_cast<const list *> (n); ll != nullptr)
            return data::functional::write (o, ll->List);

        if (const let *l = dynamic_cast<const let *> (n); l != nullptr) {
            o << "let ";
            auto b = l->Values.begin ();

            if (b != l->Values.end ()) {
                o << b->Key << " -> " << b->Value;
                while (true) {
                    b++;
                    if (b == l->Values.end ()) break;
                    o << ", " << b->Key << " -> " << b->Value;
                }
            }

            return o << " in " << l->In;
        }

        if (const dif *df = dynamic_cast<const dif *> (n); df != nullptr)
            return o << "if " << df->If << " then " << df->Then << " else " << df->Else;

        if (const blank *bl = dynamic_cast<const blank *> (n); bl != nullptr)
            return o << "_" << bl->Name;

        if (const typed *y = dynamic_cast<const typed *> (n); y != nullptr)
            return o << y->Match << " : " << y->Required;

        throw data::exception {} << "incomplete method: << expression; expression.cpp.";
    }

    std::ostream &operator << (std::ostream &o, const form *n) {
        return write (o, n, max_precedence);
    }

    std::ostream &write_binary (std::ostream &o, const binop &b) {
        data::stack<expression> body = b.Body;
        if (size (body) < 2) throw data::exception {} << "invalid binary operation " << b.Operand;

        write (o, first (body).get (), b.Operand);
        body = rest (body);
        do {
            write (o << " " << b.Operand << " ", first (body).get (), b.Operand);
            body = rest (body);
        } while (!empty (body));
        return o;
    }

    std::ostream &write_unary (std::ostream &o, const unop &u) {
        return write (o << u.Operand, u.Body.get (), precedence::unary);
    }

    std::ostream &write_call (std::ostream &o, const call &c) {
        write (o << "(", c.Fun.get (), precedence::call);
        auto args = c.Args;
        while (!empty (args)) {
            write (o << " ", first (args).get (), precedence::call);
            args = rest (args);
        }
        return o << ")";
    }

}
