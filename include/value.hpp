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

	template <typename Y, typename ...X> struct leaf<Y (*)(X...)> final : value {
		Y (*Value)(X...);
		leaf (Y (*v)(X...)) : Value {v} {}

		static expression make (Y (*)(X...));

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
	template <typename Y, typename ... X> using built_in_function = leaf<Y (*)(X...)>;

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
	}

	template <typename T> std::ostream inline &leaf<T>::write (std::ostream &o) const {
		return write_leaf<T> {} (o, Value);
	}

	template <typename Y, typename ...X> std::ostream inline &leaf<Y (*)(X...)>::write (std::ostream &o) const {
		return o << "(*)";
	}

	template <typename T> bool inline leaf<T>::operator == (const value &x) const {
		if (const leaf<T> *c = dynamic_cast<const leaf<T> *> (&x); c != nullptr)
			return this->Value == c->Value;

		return false;
	}

	template <typename Y, typename ...X> bool inline leaf<Y (*)(X...)>::operator == (const value &x) const {
		if (const leaf<Y (*)(X...)> *c = dynamic_cast<const leaf<Y (*)(X...)> *> (&x); c != nullptr)
			return this->Value == c->Value;

		return false;
	}

	template <typename T> expression inline leaf<T>::make (const T &x) {
		return expression {std::static_pointer_cast<const node> (std::make_shared<leaf<T>> (x))};
	}

	template <typename Y, typename ...X> expression inline leaf<Y (*)(X...)>::make (Y (*x)(X...)) {
		return expression {std::static_pointer_cast<const node> (std::make_shared<leaf<Y (*)(X...)>> (x))};
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

		template <typename Y, typename X> struct base_type<Y (*)(const X &)> {
			type operator () () {
				return binary_operation::make (binary_operand::intuitionistic_implies,
					base_type<X> {} (), base_type<Y> {} ());
			}
		};

		template <typename Z, typename X, typename ... Y> struct base_type<Z (*)(const X &, Y...)> {
			type operator () () {
				return binary_operation::make (binary_operand::intuitionistic_implies,
					base_type<X> {} (), base_type<Z (*)(Y...)> {} ());
			}
		};

		template <typename T> bool inline leaf_cast<T>::operator () (Type t) {
			return t >= base_type<T> {} ();
		}

	}

	template <typename T> bool inline leaf<T>::cast (const machine &, Type t) const {
		return leaf_cast<T> {} (t);
	}

	template <typename Y, typename ...X> bool inline leaf<Y (*)(X...)>::cast (const machine &, Type t) const {
		return leaf_cast<Y (*)(X...)> {} (t);
	}

	template <typename T> expression inline leaf<T>::operator () (data::stack<expression> x) const {
		return {};
	};

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
				expression first = data::first (stack);

				using type = std::remove_const_t<std::remove_reference_t<A>>;

				const leaf<type> *v = dynamic_cast<const leaf<type> *> (first.get ());
				// this should also not happen because we check earlier.
				if (v == nullptr) throw data::exception {} << "built-in function called with invalid type.";

				return expand_stack<B...> {}.template expand<Y, Z..., A> (f, data::rest (stack), z..., v->Value);
			}
		};
	}

	template <typename Y, typename ...X> expression leaf<Y (*)(X...)>::operator () (data::stack<expression> x) const {
		if (data::size (x) < sizeof...(X)) return expression {};
		expression result = leaf<Y>::make (expand_stack<X...> {}.template expand<Y (*)(X...)> (Value, x));
		if (data::size (x) == sizeof...(X)) return result;
		return call::make (result, data::drop (x, sizeof...(X)));
	};
}

#endif
