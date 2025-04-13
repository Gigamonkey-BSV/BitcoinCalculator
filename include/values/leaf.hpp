#ifndef BITCOIN_CALCULATOR_VALUE_LEAF
#define BITCOIN_CALCULATOR_VALUE_LEAF

#include <value.hpp>
#include <values/list.hpp>

namespace Diophant {

    namespace secp256k1 = Gigamonkey::secp256k1;
    using uint256 = data::uint256_little;
    using uint512 = data::uint512_little;

    template <typename T> struct leaf final : value {
        T Value;
        leaf (const T &t) : Value {t} {}

        static expression make (const T &);

        bool cast (const machine &, const node &) const final override;
        std::ostream &write (std::ostream &) const final override;
        bool operator == (const node &) const final override;
    };

    template <typename Y, typename ...X> struct leaf<Y (*)(X...)> final : value {
        Y (*Value)(X...);
        leaf (Y (*v)(X...)) : Value {v} {}

        static expression make (Y (*)(X...));

        bool cast (const machine &, const node &) const final override;
        std::ostream &write (std::ostream &) const final override;
        bool operator == (const node &) const final override;

        expression operator () (data::stack<expression>) const final override;
    };

    using natural = leaf<data::N>;
    using integer = leaf<data::Z>;

    using byte = leaf<data::byte>;
    using string = leaf<data::string>;
    using scriptnum = leaf<Bitcoin::integer>;
    using pubkey = leaf<secp256k1::pubkey>;
    using secret = leaf<uint256>;
    using sat = leaf<Bitcoin::satoshi>;
    template <typename... X> using tuple = leaf<std::tuple<X...>>;
    template <typename X> using stack = leaf<data::stack<X>>;
    template <typename Y, typename ... X> using built_in_function = leaf<Y (*)(X...)>;

    namespace {
        template <typename T> struct write_leaf {
            std::ostream &operator () (std::ostream &o, const T &t) {
                return o << t;
            }
        };

        template <> struct write_leaf<uint256> {
            std::ostream &operator () (std::ostream &o, const uint256 &t) {
                return o << std::dec << t;
            }
        };

        template <> struct write_leaf<data::byte> {
            std::ostream &operator () (std::ostream &o, const data::byte &t) {
                return data::encoding::hex::write (o << "0x", data::bytes {{t}});
            }
        };

        template <> struct write_leaf<secp256k1::pubkey> {
            std::ostream &operator () (std::ostream &o, const secp256k1::pubkey &p) {
                return data::encoding::hex::write (o, static_cast<const data::bytes &> (p));
            }
        };

        template <> struct write_leaf<Bitcoin::integer> {
            std::ostream &operator () (std::ostream &o, const Bitcoin::integer &t) {
                return data::encoding::hexidecimal::write (o, t);
            }
        };

        template <typename... X> struct write_leaf<std::tuple<X...>> {
            template <int index>
            std::ostream &write (std::ostream &o, const std::tuple<X...> &x) {
                if constexpr (index >= std::tuple_size<std::tuple<X...>>::value) return o;
                else return write<index + 1>
                    (write_leaf<std::remove_const_t<data::unref<decltype(std::get<index> (x))>>> {} (o << ", ", std::get<index> (x)), x);
            }

            std::ostream &operator () (std::ostream &o, const std::tuple<X...> &x) {
                o << "[";
                if (std::tuple_size<std::tuple<X...>>::value > 1) {
                    write_leaf<std::remove_const_t<data::unref<decltype(std::get<0> (x))>>> {} (o, std::get<0> (x));
                    write<1> (o, x);
                }
                return o << "]";
            }
        };

        template <typename X> struct write_leaf<data::stack<X>> {
            std::ostream &operator () (std::ostream &o, const data::stack<X> &t);
        };
    }

    template <typename T> std::ostream inline &leaf<T>::write (std::ostream &o) const {
        return write_leaf<T> {} (o, Value);
    }

    template <typename Y, typename ...X> std::ostream inline &leaf<Y (*)(X...)>::write (std::ostream &o) const {
        return o << "(*)";
    }

    template <typename T> bool inline leaf<T>::operator == (const node &x) const {
        if (const leaf<T> *c = dynamic_cast<const leaf<T> *> (&x); c != nullptr)
            return this->Value == c->Value;

        return false;
    }

    template <typename Y, typename ...X> bool inline leaf<Y (*)(X...)>::operator == (const node &x) const {
        if (const leaf<Y (*)(X...)> *c = dynamic_cast<const leaf<Y (*)(X...)> *> (&x); c != nullptr)
            return this->Value == c->Value;

        return false;
    }

    template <typename T> expression inline leaf<T>::make (const T &x) {
        return expression {std::static_pointer_cast<node> (std::make_shared<leaf<T>> (x))};
    }

    template <typename Y, typename ...X> expression inline leaf<Y (*)(X...)>::make (Y (*x)(X...)) {
        return expression {std::static_pointer_cast<node> (std::make_shared<leaf<Y (*)(X...)>> (x))};
    }

    namespace {
        template <typename T> struct leaf_cast {
            bool operator () (Machine, const node &t);
        };

        template <typename T> struct base_type;

        template <> struct base_type<data::byte> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (8))});
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

        template <> struct base_type<uint256> {
            type operator () () {
                return symbol::make ("secret");
            }
        };

        template <> struct base_type<data::N> {
            type operator () () {
                return symbol::make ("natural");
            }
        };

        template <> struct base_type<data::Z> {
            type operator () () {
                return symbol::make ("integer");
            }
        };

        template <typename ...X> struct base_type<std::tuple<X...>> {
            template <int index>
            data::stack<expression> base () {
                if constexpr (index >= std::tuple_size<std::tuple<X...>>::value)
                    return data::prepend (base<index + 1> (), base_type<decltype(std::get<index> ())> {} ());
                else return data::stack<expression> {};
            }

            type operator () () {
                return type {list::make (base<0> ())};
            }
        };

        template <typename X> struct base_type<data::stack<X>> {
            type operator () ();
        };

        template <typename Y, typename X> struct base_type<Y (*)(const X &)> {
            type operator () () {
                return binop::make (binary_operand::intuitionistic_implies,
                    base_type<X> {} (), base_type<Y> {} ());
            }
        };

        template <typename Z, typename X, typename ... Y> struct base_type<Z (*)(const X &, Y...)> {
            type operator () () {
                return binop::make (binary_operand::intuitionistic_implies,
                    base_type<X> {} (), base_type<Z (*)(Y...)> {} ());
            }
        };

        template <typename T> bool inline leaf_cast<T>::operator () (Machine m, const node &t) {
            auto n = impartial_ordering::equal | impartial_ordering::superset;
            auto x = type::compare (m, t, base_type<T> {} ());
            return data::byte (x & n) && !data::byte (x & ~n);
        }

    }

    template <typename T> bool inline leaf<T>::cast (const machine &m, const node &t) const {
        return leaf_cast<T> {} (m, t);
    }

    template <typename Y, typename ...X> bool inline leaf<Y (*)(X...)>::cast (const machine &m, const node &t) const {
        return leaf_cast<Y (*)(X...)> {} (m, t);
    }

    namespace {

        template <typename ...X> struct expand_stack;

        template <> struct expand_stack<> {
            template <typename Y, typename... Z>
            auto expand (Y f, data::stack<expression> stack, Z... z) {
                return f (z...);
            }
        };

        template <typename A, typename ...B> struct expand_stack<A, B...> {
            template <typename Y, typename... Z>
            auto expand (Y f, data::stack<expression> stack, Z... z) {
                // this should not happen because we check earlier.
                if (data::empty (stack)) throw data::exception {} << "try to expand empty argument list";
                pattern first = data::first (stack);

                using type = std::remove_const_t<std::remove_reference_t<A>>;

                const leaf<type> *v = dynamic_cast<const leaf<type> *> (first.get ());
                // this should also not happen because we check earlier.
                if (v == nullptr) throw data::exception {} << "built-in function called with invalid type.";

                return expand_stack<B...> {}.template expand<Y, Z..., A> (f, data::rest (stack), z..., v->Value);
            }
        };
    }

    template <typename Y, typename ...X> expression leaf<Y (*)(X...)>::operator () (data::stack<expression> x) const {
        if (data::size (x) < sizeof...(X)) return {};
        expression result = leaf<Y>::make (expand_stack<X...> {}.template expand<Y (*)(X...)> (Value, x));
        if (data::size (x) == sizeof...(X)) return result;
        return call::make (result, data::drop (x, sizeof...(X)));
    };
}

#endif

