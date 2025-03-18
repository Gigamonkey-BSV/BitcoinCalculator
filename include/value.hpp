#ifndef BITCOIN_CALCULATOR_VALUE
#define BITCOIN_CALCULATOR_VALUE

#include <machine.hpp>
#include <data/function.hpp>
#include <gigamonkey/wif.hpp>
#include <gigamonkey/address.hpp>
#include <gigamonkey/numbers.hpp>

namespace Diophant {

    namespace secp256k1 = Gigamonkey::secp256k1;
    using uint256 = data::uint256;

    struct value : node {
        virtual ~value () {}
        virtual data::maybe<casted> cast (const machine &, const type &) const = 0;
        virtual std::ostream &write (std::ostream &) const = 0;
    };

    struct list final : value {
        data::stack<expression> List;

        static expression make (data::stack<expression>);

        data::maybe<casted> cast (const machine &, const type &) const final override;
        std::ostream &write (std::ostream &) const final override;
    };

    struct lambda final : value {
        data::stack<symbol> Args;
        expression Body;

        static expression make (data::stack<symbol> args, expression body);

        data::maybe<casted> cast (const machine &, const type &) const final override;
        std::ostream &write (std::ostream &) const final override;
    };

    template <typename T> struct leaf final : value {
        T Value;
        leaf (const T &t) : Value {t} {}

        static expression make (const T &);

        data::maybe<casted> cast (const machine &, const type &) const final override;
        std::ostream &write (std::ostream &) const final override;
    };

    using byte = leaf<data::byte>;
    using string = leaf<data::string>;
    using scriptnum = leaf<Bitcoin::integer>;
    using pubkey = leaf<secp256k1::pubkey>;
    using secret = leaf<secp256k1::secret>;
    using sat = leaf<Bitcoin::satoshi>;
    template <typename Y, typename ... X> using built_in_function = leaf<std::function<Y (X...)>>;

    template <typename T> expression inline leaf<T>::make (const T &x) {
        return expression {std::static_pointer_cast<const node> (std::make_shared<leaf<T>> (x))};
    }
}

#endif
