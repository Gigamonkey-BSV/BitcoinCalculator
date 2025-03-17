#include <value.hpp>

namespace Diophant {

    bool operator == (Expression A, Expression B) {
        const node *a = A.get ();
        const node *b = B.get ();

        if (a == b) return true;


        throw data::exception {} << "incomplete method: << expression == expressions";
    }

    std::ostream &operator << (std::ostream &o, Expression E) {
        const node *e = E.get ();

        if (e == nullptr) return o << "nil";

        if (const value *v = dynamic_cast<const value *> (e); v != nullptr)
            return v->write (o);

        if (const symbol *x = dynamic_cast<const symbol *> (e); x != nullptr)
            return o << static_cast<const std::string &> (*x);

        throw data::exception {} <<
            "incomplete method: << expression; expression.cpp; we need something or precedence of operators.";
    }

}
