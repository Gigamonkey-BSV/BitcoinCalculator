#include <values/list.hpp>
#include <values/struct.hpp>
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

        if (const unop *u = dynamic_cast<const unop *> (a); u != nullptr) {
            const unop *v = dynamic_cast<const unop *> (b);
            return v == nullptr ? false: u->Operand == v->Operand && u->Body == v->Body;
        }

        if (const binop *b = dynamic_cast<const binop *> (a); b != nullptr) {
            const binop *c = dynamic_cast<const binop *> (b);
            return c == nullptr ? false:
                b->Operand == c->Operand && b->Body == c->Body;
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

        if (const dif *df = dynamic_cast<const dif *> (a); df != nullptr) {
            const dif *fi = dynamic_cast<const dif *> (b);
            return fi == nullptr ? false: df->If == fi->If && df->Then == fi->Then && df->Else == fi->Else;
        }

        if (const let *l = dynamic_cast<const let *> (a); l != nullptr) {
            const let *m = dynamic_cast<const let *> (b);
            return m == nullptr ? false: l->Values == m->Values && l->In == m->In;
        }

        throw data::exception {} << "incomplete method: expression == expressions; trying to evaluate " << A << " == " << B;
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
        if (data::size (body) < 2) throw data::exception {} << "invalid binary operation " << b.Operand;

        write (o, body.first ().get (), b.Operand);
        body = data::rest (body);
        do {
            write (o << " " << b.Operand << " ", body.first ().get (), b.Operand);
            body = data::rest (body);
        } while (!data::empty (body));
        return o;
    }

    std::ostream &write_unary (std::ostream &o, const unop &u) {
        return write (o << u.Operand, u.Body.get (), precedence::unary);
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
