#include <Diophant/nodes.hpp>
#include <Diophant/replace.hpp>

namespace Diophant {

    bool let::operator == (const node &n) const {
        const let *l = static_cast<const let *> (&n);
        if (l == nullptr || size (Values) != size (l->Values)) return false;

        replacements r {};
        auto vals_left = Values;
        auto vals_right = l->Values;
        while (!empty (vals_left)) {
            auto val_left = first (vals_left);
            auto val_right = first (vals_left);
            if (replace (val_left.Value, r) != val_right.Value) return false;
            r = r.insert (val_left.Key, symbol::make (val_right.Key));
            vals_left = rest (vals_left);
            vals_right = rest (vals_right);
        }

        return replace (In, r) == l->In;
    }
}
