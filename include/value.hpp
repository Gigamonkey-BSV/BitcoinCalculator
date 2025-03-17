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
    using byte = data::byte;

    struct value : node {
        virtual ~value () {}
        virtual maybe<casted> cast (const machine &, const type &) const = 0;
    };

    struct list final : value {
        stack<expression> List;
        static expression make (stack<expression>);
        maybe<casted> cast (const machine &, const type &) const final override;
    };

    struct lambda final : value {
        stack<symbol> Args;
        expression Body;
        static expression make (stack<symbol> args, expression body);
        maybe<casted> cast (const machine &, const type &) const final override;
    };

    template <typename T> struct leaf final : value {
        T Value;
        static expression make (const T &);
        maybe<casted> cast (const machine &, const type &) const final override;
    };

    using Dbyte = leaf<byte>;
    using Dstring = leaf<string>;
    using Dscriptnum = leaf<Bitcoin::integer>;
    using Dpubkey = leaf<secp256k1::pubkey>;
    using Dsecret = leaf<secp256k1::secret>;
    using Dsat = leaf<Bitcoin::satoshi>;
    template <typename Y, typename ... X> using built_in_function = leaf<std::function<Y (X...)>>;

}

#endif
