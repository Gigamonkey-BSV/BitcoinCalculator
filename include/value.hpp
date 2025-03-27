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
		// return undefined if the arguments don't fit.
		virtual expression operator () (data::stack<expression>) const = 0;
	};

	struct nil final : value {

		static Expression make () {
			static expression expr {std::static_pointer_cast<node> (std::make_shared<nil> ())};
			return expr;
		}

		bool cast (const machine &, Type t) const final override {
			return t > type {make ()};
		}

		std::ostream &write (std::ostream &o) const final override {
			return o << "nil";
		}

		bool operator == (const value &v) const final override {
			const nil *n = dynamic_cast<const nil *> (&v);
			return n != nullptr;
		}

		expression operator () (data::stack<expression>) const final override {
			return expression {};
		}
	};
}

#endif
