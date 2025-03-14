#include <machine.hpp>

namespace Diophant {

    machine evaluate_symbol (machine m, const symbol *x);
    machine evaluate_list (machine m, const list *ls);
    machine evaluate_binary_operation (machine m, const binary_operation *b);
    machine evaluate_unary_operation (machine m, const unary_operation *u);
    machine evaluate_call (machine m, const call *c);

    machine evaluate_round (machine m, const node *p) {
        if (p == nullptr) return m;

        if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr)
            return evaluate_symbol (m, x);
        if (const list *ls = dynamic_cast<const list *> (p); ls != nullptr)
            return evaluate_list (m, ls);
        if (const binary_operation *b = dynamic_cast<const binary_operation *> (p); b != nullptr)
            return evaluate_binary_operation (m, b);
        if (const unary_operation *u = dynamic_cast<const unary_operation *> (p); u != nullptr)
            return evaluate_unary_operation (m, u);
        if (const call *c = dynamic_cast<const call *> (c); c != nullptr)
            return evaluate_call (m, c);

        return m;
    }

    machine machine::evaluate (expression e) {
        const node *p = e.get ();

        machine m = evaluate_round (*this, p);
        while (true) {
            machine mm = evaluate_round (m, p);
            if (mm.Last == m.Last) return m;
            m == mm;
        }
    }

}
