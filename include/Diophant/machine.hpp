#ifndef BITCOIN_CALCULATOR_MACHINE
#define BITCOIN_CALCULATOR_MACHINE

#include <Diophant/nodes.hpp>
#include <Diophant/pattern.hpp>
#include <Diophant/replace.hpp>

namespace Diophant {

    struct statement {
        data::maybe<pattern> Subject;
        expression Predicate;
        statement (Pattern subject) : Subject {subject}, Predicate {} {}
        statement (Expression predicate): Subject {}, Predicate {predicate} {}
        statement (Pattern subject, Expression predicate): Subject {subject}, Predicate {predicate} {}
    };

    std::ostream &operator << (std::ostream &, const statement &);

    using program = data::stack<statement>;

    // TODO get rid of this. We are not going to use this.
    struct casted final : node {
        type Cast;

        // if there is no expression, this represents an undefined value.
        expression Def;

        casted (Type);
        casted (Type, Expression);

        static expression make (Type);
        static expression make (Type, Expression);

        bool operator == (const node &n) const final override {
            const casted *x = dynamic_cast<const casted *> (&n);
            return x != nullptr && this->Cast == x->Cast && this->Def == x->Def;
        }
    };

    std::ostream &operator << (std::ostream &o, const casted &cx);

    struct transformation {
        data::stack<pattern> Arguments;
        casted Value;

        // throws exception if two transformations
        // are not either disjoint or one is a subset of the other.
        std::partial_ordering operator <=> (const transformation) const;
    };

    std::ostream &operator << (std::ostream &o, const transformation &tf);

    struct machine {

        // TODO return type needs to go after args.
        machine declare (symbol x) const;
        machine declare (symbol x, data::stack<pattern> arg) const;

        machine declare (unary_operand op, pattern in) const;
        machine declare (binary_operand op, pattern left, pattern right) const;

        machine declare (symbol x, type of) const;
        machine declare (symbol x, type of, data::stack<pattern> arg) const;

        machine declare (unary_operand op, type of, pattern in) const;
        machine declare (binary_operand op, type of, pattern left, pattern right) const;

        machine define (symbol x, type of, expression as) const;
        machine define (symbol x, type of, data::stack<pattern> arg, expression as) const;

        machine define (unary_operand op, type of, pattern in, expression as) const;
        machine define (binary_operand op, type of, pattern left, pattern right, expression as) const;

        machine define (symbol x, expression as) const;
        machine define (symbol x, data::stack<pattern> arg, expression as) const;

        machine define (unary_operand op, pattern in, expression as) const;
        machine define (binary_operand op, pattern left, pattern right, expression as) const;

        bool valid () const;

        expression evaluate (Expression) const;

        struct result;

        result evaluate (const statement &) const;
        result evaluate (program) const;

        bool operator == (const machine &) const;

        struct autocast {
            type From;
            type To;
            expression Function;
        };

        match_result match (data::stack<pattern>, data::stack<expression>,
            data::list<machine::autocast> conversions = {}) const;

        using definition = data::either<casted, data::stack<transformation>>;

        using symbol_defs = data::map<symbol, definition>;
        using unary_defs = data::map<unary_operand, data::stack<transformation>>;
        using binary_defs = data::map<binary_operand, data::stack<transformation>>;

        symbol_defs SymbolDefinitions {};
        unary_defs UnaryDefinitions {};
        binary_defs BinaryDefinitions {};

        machine (symbol_defs xd, unary_defs ud, binary_defs bd):
            SymbolDefinitions {xd}, UnaryDefinitions {ud}, BinaryDefinitions {bd} {}
        machine () {}

    };

    struct machine::result {
        machine Machine;
        expression Expression;
    };

    machine initialize ();

    inline casted::casted (Type t): Cast {t}, Def {} {}

    inline casted::casted (Type t, Expression x): Cast {t}, Def {x} {}

    expression inline casted::make (Type t) {
        return expression {std::static_pointer_cast<node> (std::make_shared<casted> (t))};
    }

    expression inline casted::make (Type t, Expression x) {
        return expression {std::static_pointer_cast<node> (std::make_shared<casted> (t, x))};
    }

    machine inline machine::declare (symbol x) const {
        return define (x, type {}, expression {});
    }

    machine inline machine::declare (symbol x, data::stack<pattern> arg) const {
        return define (x, type {}, arg, expression {});
    }

    machine inline machine::declare (unary_operand op, pattern in) const {
        return define (op, type {}, in, expression {});
    }

    machine inline machine::declare (binary_operand op, pattern left, pattern right) const {
        return define (op, type {}, left, right, expression {});
    }

    machine inline machine::declare (symbol x, type of) const {
        return define (x, of, expression {});
    }

    machine inline machine::declare (symbol x, type of, data::stack<pattern> arg) const {
        return define (x, of, arg, expression {});
    }

    machine inline machine::declare (unary_operand op, type of, pattern in) const {
        return define (op, of, in, expression {});
    }

    machine inline machine::declare (binary_operand op, type of, pattern left, pattern right) const {
        return define (op, of, left, right, expression {});
    }

    std::ostream inline &operator << (std::ostream &o, const casted &cx) {
        return o << cx.Cast << " : " << cx.Def;
    }

    std::ostream inline &operator << (std::ostream &o, const transformation &tf) {
        return o << tf.Arguments << " -> " << tf.Value;
    }

    std::ostream inline &operator << (std::ostream &o, const statement &x) {
        if (!bool (x.Subject)) return o << x.Predicate;
        o << *x.Subject;
        if (x.Predicate != expression {}) o << " := " << x.Predicate;
        return o << ";";
    }

}

#endif

