#ifndef BITCOIN_CALCULATOR_VALUE
#define BITCOIN_CALCULATOR_VALUE

#include <machine.hpp>
#include <data/function.hpp>
#include <gigamonkey/wif.hpp>
#include <gigamonkey/address.hpp>
#include <gigamonkey/numbers.hpp>

namespace Diophant {

    struct value : node {
        virtual ~value () {}
        virtual bool cast (const machine &, Type) const = 0;
        virtual std::ostream &write (std::ostream &) const = 0;
        virtual bool operator == (const value &) const = 0;
        virtual expression operator () (data::stack<expression>) const = 0;
    };

    namespace secp256k1 = Gigamonkey::secp256k1;
    using uint256 = data::uint256;

    template <typename T> struct leaf final : value {
        T Value;
        leaf (const T &t) : Value {t} {}

        static expression make (const T &);

        bool cast (const machine &, Type) const final override;
        std::ostream &write (std::ostream &) const final override;
        bool operator == (const value &) const final override;

        // return nil if the args don't fit.
        // if there are too many args, return a call expression with the rest on the call.
        expression operator () (data::stack<expression>) const final override;
    };

    using byte = leaf<data::byte>;
    using string = leaf<data::string>;
    using scriptnum = leaf<Bitcoin::integer>;
    using pubkey = leaf<secp256k1::pubkey>;
    using secret = leaf<secp256k1::secret>;
    using sat = leaf<Bitcoin::satoshi>;
    template <typename Y, typename ... X> using built_in_function = leaf<std::function<Y (X...)>>;

    namespace {
        template <typename T> struct write_leaf {
            std::ostream &operator () (std::ostream &o, const T &t) {
                return o << t;
            }
        };

        template <> struct write_leaf<secp256k1::secret> {
            std::ostream &operator () (std::ostream &o, const secp256k1::secret &t) {
                return o << t.Value;
            }
        };

        template <> struct write_leaf<Bitcoin::integer> {
            std::ostream &operator () (std::ostream &o, const Bitcoin::integer &t) {
                data::encoding::hexidecimal::write (o, t);
                return o;
            }
        };

        template <typename Y, typename ... X> struct write_leaf<std::function<Y (X...)>> {
            std::ostream &operator () (std::ostream &o, const std::function<Y (X...)> &) {
                return o << "(*)";
            }
        };
    }

    template <typename T> std::ostream inline &leaf<T>::write (std::ostream &o) const {
        return write_leaf<T> {} (o, Value);
    }

    namespace {
        template <typename T> struct equal_leaf {
            bool operator () (const T &a, const T &b) {
                return a == b;
            }
        };

        template <typename Y, typename ... X> struct equal_leaf<std::function<Y (X...)>> {
            bool operator () (const std::function<Y (X...)> &, const std::function<Y (X...)> &) {
                return false;
            }
        };
    }

    template <typename T> bool inline leaf<T>::operator == (const value &x) const {
        if (const leaf<T> *c = dynamic_cast<const leaf<T> *> (&x); c != nullptr)
            return equal_leaf<T> {} (this->Value, c->Value);

        return false;
    }

    template <typename T> expression inline leaf<T>::make (const T &x) {
        return expression {std::static_pointer_cast<const node> (std::make_shared<leaf<T>> (x))};
    }

    namespace {
        template <typename T> struct leaf_cast {
            bool operator () (Type t);
        };

        template <typename T> struct base_type;

        template <> struct base_type<data::byte> {
            type operator () () {
                return symbol::make ("byte");
            }
        };

        template <> struct base_type<data::string> {
            type operator () () {
                return symbol::make ("string");
            }
        };

        template <> struct base_type<Bitcoin::integer> {
            type operator () () {
                return symbol::make ("scriptnum");
            }
        };

        template <> struct base_type<secp256k1::pubkey> {
            type operator () () {
                return symbol::make ("pubkey");
            }
        };

        template <> struct base_type<secp256k1::secret> {
            type operator () () {
                return symbol::make ("secret");
            }
        };

        template <typename Y, typename X> struct base_type<std::function<Y (const X &)>> {
            type operator () () {
                return binary_operation::make (binary_operand::intuitionistic_implies,
                    base_type<X> {} (), base_type<Y> {} ());
            }
        };

        template <typename Z, typename X, typename ... Y> struct base_type<std::function<Z (const X &, Y...)>> {
            type operator () () {
                return binary_operation::make (binary_operand::intuitionistic_implies,
                    base_type<X> {} (), base_type<std::function<Z (Y...)>> {} ());
            }
        };

        template <typename T> bool inline leaf_cast<T>::operator () (Type t) {
            return t >= base_type<T> {} ();
        }

    }

    template <typename T> bool inline leaf<T>::cast (const machine &, Type t) const {
        return leaf_cast<T> {} (t);
    }

    namespace {
        template <typename T> struct leaf_call {
            expression operator () (data::stack<expression>) {
                return {};
            }
        };

        template <typename Y, typename ... X> struct leaf_call<std::function<Y (X...)>> {
            expression operator () (data::stack<expression>) {
                throw data::exception {} << "we don't know how to do this yet";
            }
        };
    }

    template <typename T> expression leaf<T>::operator () (data::stack<expression> x) const {
        return leaf_call<T> {} (x);
    };
}

#endif
