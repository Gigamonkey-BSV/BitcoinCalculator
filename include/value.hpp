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
		virtual bool cast (const machine &, const node &) const = 0;
		virtual std::ostream &write (std::ostream &) const = 0;
		// return undefined if the arguments don't fit.
		virtual expression operator () (data::stack<expression>) const {
			return {};
		};
	};

	struct nil final : value {

		static Expression make () {
			static expression expr {std::static_pointer_cast<node> (std::make_shared<nil> ())};
			return expr;
		}

		bool cast (const machine &m, const node &n) const final override {
			auto x = type::compare (m, n, type {make ()});
			return x == impartial_ordering::equal || x == impartial_ordering::superset;
		}

		std::ostream &write (std::ostream &o) const final override {
			return o << "<nil>";
		}

		bool operator == (const node &v) const final override {
			const nil *n = dynamic_cast<const nil *> (&v);
			return n != nullptr;
		}
	};
}

#endif
