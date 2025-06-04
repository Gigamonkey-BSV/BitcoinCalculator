#ifndef BITCOIN_CALCULATOR_VALUE_LEAF
#define BITCOIN_CALCULATOR_VALUE_LEAF

#include <data/types.hpp>
#include <Diophant/value.hpp>
#include <Diophant/values/list.hpp>

namespace Diophant {

    namespace secp256k1 = Gigamonkey::secp256k1;

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

    using uint8 = leaf<uint8_t>;
    using int8 = leaf<int8_t>;
    using uint8_little = leaf<uint8_t>;
    using int8_little = leaf<int8_t>;
    using uint8_big = leaf<uint8_t>;
    using int8_big = leaf<int8_t>;

    using uint16 = leaf<data::uint16>;
    using int16 = leaf<data::int16>;
    using uint16_little = leaf<data::uint16_little>;
    using int16_little = leaf<data::int16_little>;
    using uint16_big = leaf<data::uint16_big>;
    using int16_big = leaf<data::int16_big>;

    using uint24 = leaf<data::uint24_little>;
    using int24 = leaf<data::int24_little>;
    using uint24_little = leaf<data::uint24_little>;
    using int24_little = leaf<data::int24_little>;
    using uint24_big = leaf<data::uint24_big>;
    using int24_big = leaf<data::int24_big>;

    using uint32 = leaf<data::uint32>;
    using int32 = leaf<data::int32>;
    using uint32_little = leaf<data::uint32_little>;
    using int32_little = leaf<data::int32_little>;
    using uint32_big = leaf<data::uint32_big>;
    using int32_big = leaf<data::int32_big>;

    using uint64 = leaf<data::uint64>;
    using int64 = leaf<data::int64>;
    using uint64_little = leaf<data::uint64_little>;
    using int64_little = leaf<data::int64_little>;
    using uint64_big = leaf<data::uint64_big>;
    using int64_big = leaf<data::int64_big>;

    using uint80 = leaf<data::uint80>;
    using int80 = leaf<data::int80>;
    using uint80_little = leaf<data::uint80_little>;
    using int80_little = leaf<data::int80_little>;
    using uint80_big = leaf<data::uint80_big>;
    using int80_big = leaf<data::int80_big>;

    using uint128 = leaf<data::uint128>;
    using int128 = leaf<data::int128>;
    using uint128_little = leaf<data::uint128_little>;
    using int128_little = leaf<data::int128_little>;
    using uint128_big = leaf<data::uint128_big>;
    using int128_big = leaf<data::int128_big>;

    using uint160 = leaf<data::uint160>;
    using int160 = leaf<data::int160>;
    using uint160_little = leaf<data::uint160_little>;
    using int160_little = leaf<data::int160_little>;
    using uint160_big = leaf<data::uint160_big>;
    using int160_big = leaf<data::int160_big>;

    using uint224 = leaf<data::uint224>;
    using int224 = leaf<data::int224>;
    using uint224_little = leaf<data::uint224_little>;
    using int224_little = leaf<data::int224_little>;
    using uint224_big = leaf<data::uint224_big>;
    using int224_big = leaf<data::int224_big>;

    using uint256 = leaf<data::uint256>;
    using int256 = leaf<data::int256>;
    using uint256_little = leaf<data::uint256_little>;
    using int256_little = leaf<data::int256_little>;
    using uint256_big = leaf<data::uint256_big>;
    using int256_big = leaf<data::int256_big>;

    using uint320 = leaf<data::uint320>;
    using int320 = leaf<data::int320>;
    using uint320_little = leaf<data::uint320_little>;
    using int320_little = leaf<data::int320_little>;
    using uint320_big = leaf<data::uint320_big>;
    using int320_big = leaf<data::int320_big>;

    using uint448 = leaf<data::uint448>;
    using int448 = leaf<data::int448>;
    using uint448_little = leaf<data::uint448_little>;
    using int448_little = leaf<data::int448_little>;
    using uint448_big = leaf<data::uint448_big>;
    using int448_big = leaf<data::int448_big>;

    using uint512 = leaf<data::uint512>;
    using int512 = leaf<data::int512>;
    using uint512_little = leaf<data::uint512_little>;
    using int512_little = leaf<data::int512_little>;
    using uint512_big = leaf<data::uint512_big>;
    using int512_big = leaf<data::int512_big>;

    template <typename Z> using rational = leaf<data::math::fraction<Z>>;

    using boolean = leaf<bool>;
    using byte = leaf<data::byte>;
    using bytes = leaf<data::bytes>;
    using string = leaf<data::string>;
    using pubkey = leaf<secp256k1::pubkey>;
    using sat = leaf<Bitcoin::satoshi>;
    //using scriptnum = leaf<Bitcoin::integer>;
    template <typename... X> using tuple = leaf<std::tuple<X...>>;
    template <typename X> using stack = leaf<data::stack<X>>;
    template <typename Y, typename ... X> using built_in_func = leaf<Y (*)(X...)>;

    namespace {
        template <typename T> struct leaf_cast {
            bool operator () (Machine, const node &t);
        };

        template <typename T> struct base_type;

        template <> struct base_type<bool> {
            type operator () () {
                return symbol::make ("bool");
            }
        };

        template <> struct base_type<data::byte> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (8))});
            }
        };

        template <> struct base_type<data::int8> {
            type operator () () {
                return call::make (symbol::make ("int"), {natural::make (data::N (8))});
            }
        };

        template <> struct base_type<data::uint16> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (16))});
            }
        };

        template <> struct base_type<data::int16> {
            type operator () () {
                return call::make (symbol::make ("int"), {natural::make (data::N (16))});
            }
        };

        template <> struct base_type<data::uint32> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (32))});
            }
        };

        template <> struct base_type<data::int32> {
            type operator () () {
                return call::make (symbol::make ("int"), {natural::make (data::N (32))});
            }
        };

        template <> struct base_type<data::uint64> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (64))});
            }
        };

        template <> struct base_type<data::int64> {
            type operator () () {
                return call::make (symbol::make ("int"), {natural::make (data::N (64))});
            }
        };

        template <std::size_t bytes>
        struct base_type<data::endian_integral<false, data::endian::order::little, bytes>> {
            type operator () () {
                return call::make (symbol::make ("uint_little"), {natural::make (data::N (bytes * 8))});
            }
        };

        template <std::size_t bytes>
        struct base_type<data::endian_integral<true, data::endian::order::little, bytes>> {
            type operator () () {
                return call::make (symbol::make ("int_little"), {natural::make (data::N (bytes * 8))});
            }
        };

        template <std::size_t bytes>
        struct base_type<data::endian_integral<false, data::endian::order::big, bytes>> {
            type operator () () {
                return call::make (symbol::make ("uint_big"), {natural::make (data::N (bytes * 8))});
            }
        };

        template <std::size_t bytes>
        struct base_type<data::endian_integral<true, data::endian::order::big, bytes>> {
            type operator () () {
                return call::make (symbol::make ("int_big"), {natural::make (data::N (bytes * 8))});
            }
        };

        template <size_t size> struct base_type<data::uint_little<size>> {
            type operator () () {
                return call::make (symbol::make ("uint_little"), {natural::make (data::N (size * 8))});
            }
        };

        template <size_t size> struct base_type<data::int_little<size>> {
            type operator () () {
                return call::make (symbol::make ("int_little"), {natural::make (data::N (size * 8))});
            }
        };

        template <size_t size> struct base_type<data::uint_big<size>> {
            type operator () () {
                return call::make (symbol::make ("uint_big"), {natural::make (data::N (size * 8))});
            }
        };

        template <size_t size> struct base_type<data::int_big<size>> {
            type operator () () {
                return call::make (symbol::make ("int_big"), {natural::make (data::N (size * 8))});
            }
        };

        template <> struct base_type<data::uint128> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (128))});
            }
        };

        template <> struct base_type<data::int128> {
            type operator () () {
                return call::make (symbol::make ("int"), {natural::make (data::N (128))});
            }
        };

        template <> struct base_type<data::uint160> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (160))});
            }
        };

        template <> struct base_type<data::int160> {
            type operator () () {
                return call::make (symbol::make ("int"), {natural::make (data::N (160))});
            }
        };

        template <> struct base_type<data::uint256> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (256))});
            }
        };

        template <> struct base_type<data::int256> {
            type operator () () {
                return call::make (symbol::make ("int"), {natural::make (data::N (256))});
            }
        };

        template <> struct base_type<data::uint512> {
            type operator () () {
                return call::make (symbol::make ("uint"), {natural::make (data::N (512))});
            }
        };

        template <> struct base_type<data::int512> {
            type operator () () {
                return call::make (symbol::make ("int"), {natural::make (data::N (512))});
            }
        };

        template <> struct base_type<data::string> {
            type operator () () {
                return symbol::make ("string");
            }
        };

        template <> struct base_type<data::bytes> {
            type operator () () {
                return symbol::make ("bytes");
            }
        };

        template <> struct base_type<Bitcoin::integer> {
            type operator () () {
                return symbol::make ("ScriptNum");
            }
        };

        template <> struct base_type<secp256k1::pubkey> {
            type operator () () {
                return symbol::make ("pubkey");
            }
        };

        template <> struct base_type<data::N> {
            type operator () () {
                return symbol::make ("N");
            }
        };

        template <> struct base_type<data::Z> {
            type operator () () {
                return symbol::make ("Z");
            }
        };

        template <typename ...X> struct base_type<std::tuple<X...>> {
            template <int index>
            data::stack<expression> base () {
                if constexpr (index >= std::tuple_size<std::tuple<X...>>::value)
                    return data::prepend (base<index + 1> (), base_type<decltype (std::get<index> ())> {} ());
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

        template <typename Y, typename X> struct base_type<Y (*)(X)> {
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

        template <typename Z, typename X, typename ... Y> struct base_type<Z (*)(X, Y...)> {
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
        template <typename T> struct write_leaf {
            std::ostream &operator () (std::ostream &o, const T &x) {
                return o << x;
            }
        };

        template <> struct write_leaf<bool> {
            std::ostream &operator () (std::ostream &o, bool b) {
                return o << std::boolalpha << b;
            }
        };

        template <> struct write_leaf<data::byte> {
            std::ostream &operator () (std::ostream &o, const data::byte &t) {
                return data::encoding::hex::write (o << "0x", data::bytes {{t}});
            }
        };

        template <> struct write_leaf<data::int8> {
            std::ostream &operator () (std::ostream &o, const data::byte &t) {
                return o << t;
            }
        };

        template <std::integral X> struct write_leaf<X> {
            std::ostream &operator () (std::ostream &o, X x) {
                return o << std::dec << x;
            }
        };

        template <> struct write_leaf<data::bytes> {
            std::ostream &operator () (std::ostream &o, const data::bytes &t) {
                return data::encoding::hex::write (o << '\'', t) << '\'';
            }
        };

        template <> struct write_leaf<data::uint256_little> {
            std::ostream &operator () (std::ostream &o, const data::uint256_little &n) {
                return o << std::dec << n;
            }
        };

        template <> struct write_leaf<data::uint256> {
            std::ostream &operator () (std::ostream &o, const data::uint256 &n) {
                return o << std::dec << n;
            }
        };

        template <> struct write_leaf<data::uint160_little> {
            std::ostream &operator () (std::ostream &o, const data::uint160_little &n) {
                return o << std::dec << n;
            }
        };

        template <> struct write_leaf<data::N> {
            std::ostream &operator () (std::ostream &o, const data::N &n) {
                return o << std::dec << n;
            }
        };

        template <> struct write_leaf<data::Z> {
            std::ostream &operator () (std::ostream &o, const data::Z &n) {
                return o << std::dec << n;
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
        return o << "(" << base_type<Y (*)(X...)> {} () << " : *)";
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

        template <typename ...X> struct expand_stack;

        template <> struct expand_stack<> {
            template <typename callable, typename... args>
            auto expand (callable f, data::stack<expression> stack, args... z) {
                return f (z...);
            }
        };

        template <typename arg1, typename ...argtypes> struct expand_stack<arg1, argtypes...> {
            // we go through the elements of the stack and add them to the function call, one by one.
            template <typename callable, typename... Z>
            auto expand (callable f, data::stack<expression> stack, Z... z) {
                // this should not happen because we check earlier.
                if (data::empty (stack)) throw data::exception {} << "try to expand empty argument list";
                pattern first = data::first (stack);

                using type = std::remove_const_t<std::remove_reference_t<arg1>>;

                const leaf<type> *v = dynamic_cast<const leaf<type> *> (first.get ());
                // this should also not happen because we check earlier.
                if (v == nullptr) {
                    std::cout << "trying to cast " << first << std::endl;
                    throw data::exception {} << "built-in function called with invalid type";
                }

                return expand_stack<argtypes...> {}.template expand<callable, Z..., arg1> (f, data::rest (stack), z..., v->Value);
            }
        };
    }

    // we try to apply a stack of expressions to a built in functon.
    template <typename return_type, typename ...args> expression leaf<return_type (*)(args...)>::operator () (data::stack<expression> x) const {
        if (data::size (x) < sizeof...(args)) return {};
        expression result = leaf<return_type>::make (expand_stack<args...> {}.template expand<return_type (*)(args...)> (Value, x));
        if (data::size (x) == sizeof...(args)) return result;
        return call::make (result, data::drop (x, sizeof...(args)));
    };
}

#endif

