#include <machine.hpp>
#include <values/list.hpp>
#include <values/lambda.hpp>

namespace Diophant {

    namespace {

        data::maybe<expression> &decl (machine &m, symbol x, type of);
        data::maybe<expression> &decl (machine &m, symbol x, type of, data::stack<pattern> arg);
        data::maybe<expression> &decl (machine &m, unary_operand op, type of, pattern in);
        data::maybe<expression> &decl (machine &m, binary_operand op, type of, pattern left, pattern right);

    }

    machine machine::declare (symbol x, type of) const {
        machine m = *this;
        decl (m, x, of);
        return m;
    }

    machine machine::declare (symbol x, type of, data::stack<pattern> arg) const {
        machine m = *this;
        decl (m, x, of, arg);
        return m;
    }

    machine machine::declare (unary_operand op, type of, pattern in) const {
        machine m = *this;
        decl (m, op, of, in);
        return m;
    }

    machine machine::declare (binary_operand op, type of, pattern left, pattern right) const {
        machine m = *this;
        decl (m, op, of, left, right);
        return m;
    }

    machine machine::define (symbol x, type of, expression as) const {
        machine m = *this;
        data::maybe<expression> &def = decl (m, x, of);
        if (!bool (def)) def = as;
        else if (*def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (symbol x, type of, data::stack<pattern> arg, expression as) const {
        machine m = *this;
        data::maybe<expression> &def = decl (m, x, of, arg);
        if (!bool (def)) def = as;
        else if (*def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (unary_operand op, type of, pattern in, expression as) const {
        machine m = *this;
        data::maybe<expression> &def = decl (m, op, of, in);
        if (!bool (def)) def = as;
        else if (*def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    machine machine::define (binary_operand op, type of, pattern left, pattern right, expression as) const {
        machine m = *this;
        data::maybe<expression> &def = decl (m, op, of, left, right);
        if (!bool (def)) def = as;
        else if (*def != as) throw data::exception {} << "definition already exists";
        return m;
    }

    namespace {

        expression evaluate_round (const machine &m, const node *p);

    }

    expression machine::evaluate (Expression e) const {
        expression last = e;
        while (true) {
            const node *p = last.get ();
            expression next = evaluate_round (*this, p);
            if (next == expression {}) return last;
            last = next;
        }
    }

    namespace {
        data::maybe<casted> cast_symbol (const machine &, const type &T, const expression &E);
        data::maybe<casted> cast_call (const machine &, const type &T, const expression &E);
        data::maybe<casted> cast_binary_operation (const machine &, const type &T, const expression &E);
        data::maybe<casted> cast_unary_operation (const machine &, const type &T, const expression &E);
    }

    // try to cast a value as a type.
    data::maybe<casted> machine::cast (const type &T, const expression &E) {
        const node *t = T.get ();
        const node *e = E.get ();

        if (e == nullptr) return t == nullptr ? data::maybe<casted> {} : data::maybe<casted> {{T, E}};

        if (const value *v = dynamic_cast<const value *> (e); v != nullptr) return v->cast (*this, T);
        if (const symbol *x = dynamic_cast<const symbol *> (e); x != nullptr)
            return cast_symbol (*this, T, E);
        if (const binary_operation *b = dynamic_cast<const binary_operation *> (e); b != nullptr)
            return cast_binary_operation (*this, T, E);
        if (const unary_operation *u = dynamic_cast<const unary_operation *> (e); u != nullptr)
            return cast_unary_operation (*this, T, E);
        if (const call *c = dynamic_cast<const call *> (e); c != nullptr)
            return cast_call (*this, T, E);

        return {};
    }

    namespace {

        struct candidate {
            replacements Replacements;
            casted Result;
            data::stack<expression> Remaining;
        };

        expression evaluate_list (const machine &m, const list *ls);

        expression evaluate_symbol (const machine &m, const symbol *x);

        expression evaluate_binary_operation (const machine &m, const binary_operation *b);

        expression evaluate_unary_operation (const machine &m, const unary_operation *u);

        expression evaluate_call (const machine &m, const call *c);

        expression evaluate_round (const machine &m, const node *p) {
            if (p == nullptr) return expression {};

            if (const symbol *x = dynamic_cast<const symbol *> (p); x != nullptr)
                return evaluate_symbol (m, x);
            if (const list *ls = dynamic_cast<const list *> (p); ls != nullptr)
                return evaluate_list (m, ls);
            if (const binary_operation *b = dynamic_cast<const binary_operation *> (p); b != nullptr)
                return evaluate_binary_operation (m, b);
            if (const unary_operation *u = dynamic_cast<const unary_operation *> (p); u != nullptr)
                return evaluate_unary_operation (m, u);
            if (const call *c = dynamic_cast<const call *> (p); c != nullptr)
                return evaluate_call (m, c);

            return expression {};
        }
    }

    data::maybe<replacements> machine::match (data::stack<pattern> p, data::stack<expression> e, data::stack<casted> known) const {
        if (data::size (p) != data::size (e)) return {};

        replacements r;
        while (!data::empty (p)) {
            auto m = match (data::first (p), data::first (e), known);
            if (!bool (m)) return {};
            for (const auto &[key, value] : *m)
                if (const auto *v = r.contains (key); v != nullptr) {
                    if (*v != value) return {};
                } else r = r.insert (key, value);

            p = p.rest ();
            e = e.rest ();
        }

        return r;
    }

    data::maybe<replacements> machine::match (const pattern p, const expression e, data::stack<casted> known) const {
        const form *z = p.get ();
        const node *n = e.get ();

        using mr = data::maybe<replacements>;

        if (const node *q = dynamic_cast<const node *> (z); q != nullptr || z == nullptr)
            return p == pattern {e} ? mr {{}} : mr {};
        else if (const blank *b = dynamic_cast<const blank *> (z); b != nullptr)
            return b->Name != "" ? mr {{{b->Name, e}}} : mr {{}};
        else if (const typed *t = dynamic_cast<const typed *> (z); t != nullptr) {
            mr r = match (t->Required, e, known);
            if (!bool (r)) return {};
            auto tt = derive_type (e);
            if (!bool (tt)) return {}; // this should really be an error.
            if (t->Match >= *tt) return r;
        }

        return {};
    }

    namespace {

        using mtf = machine::transformation;

        data::maybe<candidate> get_candidate (const machine &m, data::stack<mtf> tfs, data::stack<expression> args) {
            while (!data::empty (tfs)) {

                auto &tf = data::first (tfs);

                if (data::size (tf.Arguments) > data::size (args)) return {};

                auto match_args = data::take (args, data::size (tf.Arguments));

                data::maybe<replacements> r = m.match (tf.Arguments, match_args);

                if (bool (r)) return {{*r, tf.Value, data::drop (args, data::size (tf.Arguments))}};

                tfs = data::rest (tfs);
            }

            return {};
        }

        expression evaluate_list (const machine &m, const list *ls) {
            bool changed = false;

            data::list<expression> new_ls;
            for (Expression old_arg : data::stack<expression> (ls->List)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != expression {}) {
                    changed = true;
                    new_ls <<= new_arg;
                } else new_ls <<= old_arg;
            }

            return changed ? list::make (new_ls) : expression {};
        }

        expression evaluate_symbol (const machine &m, const symbol *x) {

            const machine::definition *v = m.SymbolDefinitions.contains (*x);
            if (v == nullptr) return expression {};

            if (!std::holds_alternative<casted> (*v)) return expression {};

            const casted &z = std::get<casted> (*v);

            if (!bool (z.Def)) throw data::exception {} << "Error: attempt to evaluate undefined pattern";

            return *z.Def;
        }

        expression evaluate_binary_operation (const machine &m, const binary_operation *b) {
            // first we evaluate function and args individually.
            bool changed = false;

            expression left = m.evaluate (b->Left);
            expression right = m.evaluate (b->Right);

            if (left != expression {}) changed = true;
            else left = b->Left;

            if (right != expression {}) changed = true;
            else right = b->Right;

            {
                const data::stack<mtf> *v = m.BinaryDefinitions.contains (b->Operator);
                if (v == nullptr) goto done;

                data::stack<mtf> tfs = *v;

                data::maybe<candidate> cx = get_candidate (m, tfs, {left, right});
                if (bool (cx)) {
                    changed = true;
                    if (!bool (cx->Result.Def)) throw data::exception {} << "Error: attempt to evaluate undefined pattern";
                    return m.evaluate (replace (*cx->Result.Def, cx->Replacements));
                }
            }

            done:
            return changed ? binary_operation::make (b->Operator, left, right) : expression {};
        }

        expression evaluate_unary_operation (const machine &m, const unary_operation *u) {
            // first we evaluate function and args individually.
            bool changed = false;
            expression body = m.evaluate (u->Body);
            if (body != expression {}) changed = true;
            else body = u->Body;

            {
                const data::stack<mtf> *v = m.UnaryDefinitions.contains (u->Operator);
                if (v == nullptr) goto done;

                data::stack<mtf> tfs = *v;

                data::maybe<candidate> cx = get_candidate (m, tfs, {body});
                if (bool (cx)) {
                    changed = true;
                    if (!bool (cx->Result.Def)) throw data::exception {} << "Error: attempt to evaluate undefined pattern";
                    return m.evaluate (replace (*cx->Result.Def, cx->Replacements));
                }
            }

            done:
            return changed ? unary_operation::make (u->Operator, body) : expression {};
        }

        expression evaluate_call (const machine &m, const call *c) {
            // first we evaluate function and args individually.
            bool changed = false;
            expression fun = m.evaluate (c->Fun);
            if (fun != expression {}) changed = true;
            else fun = c->Fun;

            data::list<expression> args;
            for (Expression old_arg : data::stack<expression> (c->Args)) {
                expression new_arg = m.evaluate (old_arg);
                if (new_arg != expression {}) {
                    changed = true;
                    args <<= new_arg;
                } else args <<= old_arg;
            }

            // next we try to match the function and args against our definitions.
            while (true) {
                const node *p = fun.get ();

                int min_args = 1;

                // this only happens once because any further nested calls would
                // have been flattened when the function was evaluated above.
                if (const call *cc = dynamic_cast<const call *> (c); cc != nullptr) {
                    // we will skip the definitions that have as many args as
                    // in the inner call or fewer, since these would
                    // have already been checked.

                    min_args += data::size (cc->Args);
                    args = cc->Args + args;
                    fun = cc->Fun;
                    p = fun.get ();
                }

                if (const lambda *n = dynamic_cast<const lambda *> (c); n != nullptr) {
                    if (data::size (n->Args) > data::size (args)) goto done;

                    changed = true;
                    data::stack<symbol> in = n->Args;
                    replacements r;

                    while (!data::empty (in)) {
                        r = r.insert (data::first (in), data::first (args));
                        in = data::rest (in);
                        args = data::rest (args);
                    }

                    fun = m.evaluate (replace (n->Body, r));

                    if (data::empty (args)) return fun;
                    continue;
                }

                // Note: here we simply find the first possible match. However,
                // in general we want to look for a unique match or a unique
                // match with automatic type conversions.
                if (const symbol *x = dynamic_cast<const symbol *> (c); x != nullptr) {
                    const machine::definition *v = m.SymbolDefinitions.contains (*x);
                    if (v == nullptr || !std::holds_alternative<data::stack<mtf>> (*v)) goto done;

                    data::stack<mtf> tfs = std::get<data::stack<mtf>> (*v);

                    while (true) {
                        if (data::empty (tfs)) goto done;
                        if (data::size (data::first (tfs).Arguments) >= min_args) break;
                        tfs = data::rest (tfs);
                    }

                    data::maybe<candidate> cx = get_candidate (m, tfs, args);
                    if (bool (cx)) {
                        changed = true;
                        if (!bool (cx->Result.Def)) throw data::exception {} << "Error: attempt to evaluate undefined pattern";
                        fun = m.evaluate (replace (*cx->Result.Def, cx->Replacements));
                        args = cx->Remaining;
                        continue;
                    }
                }

                done:
                return changed ? call::make (fun, args) : expression {};
            }
        }

        data::maybe<expression> &decl (machine &m, symbol x, type of) {
            auto *v = m.SymbolDefinitions.contains (x);

            if (v == nullptr) {
                m.SymbolDefinitions = m.SymbolDefinitions.insert (x, casted {of});
                v = m.SymbolDefinitions.contains (x);
                return std::get<casted> (*v).Def;
            }

            if (!std::holds_alternative<casted> (*v)) throw data::exception {} << "incompatible definitions already provided for " << x;

            casted &z = std::get<casted> (*v);

            if (bool (std::get<casted> (*v).Def)) throw data::exception {} << "symbol " << x << " is already defined";

            return z.Def;
        }

        // now we need to find a matching definition or add one in if it doesn't exist.
        // if we find an equal definition we can stop. If we find a subset we can stop.
        // if we find something incompatible we throw an error.
        data::maybe<expression> &insert_declaration_into_stack (data::stack<mtf> &z, type of, data::stack<pattern> arg);

        data::maybe<expression> &decl (machine &m, symbol x, type of, data::stack<pattern> arg) {
            auto *v = m.SymbolDefinitions.contains (x);

            if (v == nullptr) {
                m.SymbolDefinitions =
                    m.SymbolDefinitions.insert (x,
                        data::stack<mtf> {mtf {arg, casted {of}}});
                v = m.SymbolDefinitions.contains (x);
                return std::get<data::stack<mtf>> (*v).first ().Value.Def;
            }

            if (!std::holds_alternative<data::stack<mtf>> (*v))
                throw data::exception {} << "symbol " << x << " is already defined";

            return insert_declaration_into_stack (std::get<data::stack<mtf>> (*v), of, arg);
        }

        data::maybe<expression> &decl (machine &m, unary_operand op, type of, pattern in) {
            data::stack<mtf> *v = m.UnaryDefinitions.contains (op);

            if (v == nullptr) {
                m.UnaryDefinitions = m.UnaryDefinitions.insert (op, {machine::transformation {{in}, casted {of}}});
                v = m.UnaryDefinitions.contains (op);
                return v->first ().Value.Def;
            }

            return insert_declaration_into_stack (*v, of, {in});
        }

        data::maybe<expression> &decl (machine &m, binary_operand op, type of, pattern left, pattern right) {
            data::stack<mtf> *v = m.BinaryDefinitions.contains (op);

            if (v == nullptr) {
                m.BinaryDefinitions = m.BinaryDefinitions.insert (op, {machine::transformation {{left, right}, casted {of}}});
                v = m.BinaryDefinitions.contains (op);
                return v->first ().Value.Def;
            }

            return insert_declaration_into_stack (*v, of, {left, right});
        }

        data::maybe<casted> cast_symbol (const machine &, const type &T, const expression &E) {
            throw data::exception {} << "cast_symbol";
        }

        data::maybe<casted> cast_call (const machine &, const type &T, const expression &E) {
            throw data::exception {} << "cast_call";
        }

        data::maybe<casted> cast_binary_operation (const machine &, const type &T, const expression &E) {
            throw data::exception {} << "cast_binary_operation";
        }

        data::maybe<casted> cast_unary_operation (const machine &, const type &T, const expression &E) {
            throw data::exception {} << "cast_unary_operation";
        }

        // we need to find a matching definition or add one in if it doesn't exist.
        // if we find an equal definition we can stop. If we find a subset we can stop.
        // if we find something incompatible we throw an error.
        data::maybe<expression> &insert_declaration_into_stack (data::stack<mtf> &z, type of, data::stack<pattern> arg) {
            data::stack<mtf> back;

            while (true) {
                if (data::empty (z)) {
                    z <<= mtf {arg, casted {of}};
                    break;
                }

                // TODO: we have to do more to handle overloads here.

                back <<= data::first (z);
                z = data::rest (z);
            }

            data::maybe<expression> &val = z.first ().Value.Def;

            while (!data::empty (back)) {
                z <<= data::first (back);
                back = data::rest (back);
            }

            return val;
        }

    }

}
