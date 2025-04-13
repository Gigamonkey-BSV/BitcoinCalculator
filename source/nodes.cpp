#include <nodes.hpp>
#include <replace.hpp>

namespace Diophant {

    bool let::operator == (const node &n) const {
        const let *l = static_cast<const let *> (&n);
        if (l == nullptr || data::size (Values) != data::size (l->Values)) return false;

        replacements r {};
        auto vals_left = Values;
        auto vals_right = l->Values;
        while (!data::empty (vals_left)) {
            auto val_left = data::first (vals_left);
            auto val_right = data::first (vals_left);
            if (replace (val_left.Value, r) != val_right.Value) return false;
            r = r.insert (val_left.Key, symbol::make (val_right.Key));
            vals_left = data::rest (vals_left);
            vals_right = data::rest (vals_right);
        }

        return replace (In, r) == l->In;
    }
}
