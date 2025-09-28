#include <Diophant/parse.hpp>
#include <Diophant/parse/parser.hpp>
#include <Diophant/values/lambda.hpp>
#include <Diophant/values/list.hpp>
#include <Diophant/values/struct.hpp>
#include <Diophant/operators.hpp>

namespace Diophant {

    template program read<tao_pegtl_grammar::read_expression> (const data::string &);
    template program read<tao_pegtl_grammar::read_definition> (const data::string &);
    template program read<tao_pegtl_grammar::read_declaration> (const data::string &);
    template program read<tao_pegtl_grammar::program> (const data::string &);

    program parser::complete () const {

        if (Exp.size () > 1) throw data::exception {} << "parsing error: stack is " << Exp;

        if (Final.size () == 0) {
            if (Exp.size () == 0) return program {statement {nil::make ()}};
            return program {statement {first (Exp)}};
        }

        if (Exp.size () == 0) return reverse (Final);
        return reverse (Final >> statement {first (Exp)});
    }

    void parser::binary (binary_operand op) {
        expression x = first (Exp);
        expression z = first (rest (Exp));
        if (is_associative (op)) {
            if (const auto *bb = dynamic_cast<const binop *> (x.get ()); bb != nullptr) {
                if (bb->Operand == op) {
                    Exp = prepend (rest (rest (Exp)), binop::make (op, prepend (bb->Body, z)));
                    return;
                }
            }
        }

        Exp = prepend (rest (rest (Exp)), binop::make (op, z, x));
    }

    void parser::complete_lambda () {

        // remove all previous expressions from the stack.
        // This is done in case we start to read one lambda
        // format and then find out that it isn't valid and
        // read the other one instead.
        Exp = prepend (first (Back), lambda::make (reverse (first (Symbols)), first (Exp)));
        Symbols = rest (Symbols);
        Back = rest (Back);
    }

    void parser::open_struct () {
        Back = prepend (Back, Exp);
        Exp = {};
        Symbols >>= data::stack<symbol> {};
    }

    void parser::close_struct () {
        Exp = prepend (first (Back), dstruct::make (reverse (data::map_thread ([] (const symbol &x, const expression &p) {
            return data::entry<symbol, expression> {x, p};
        }, first (Symbols), Exp))));
        Symbols = rest (Symbols);
        Back = rest (Back);
    }

    void parser::let_open () {
        Back = prepend (Back, Exp);
        Exp = {};
        Symbols >>= data::stack<symbol> {};
    }

    void parser::let_close () {
        Exp = prepend (first (Back), let::make (reverse (data::map_thread ([] (const symbol &x, const expression &p) {
            return data::entry<const symbol, expression> {x, p};
        }, first (Symbols), rest (Exp))), first (Exp)));
        Symbols = rest (Symbols);
        Back = rest (Back);
    }

    // top entry on stack should be a declaration.
    void parser::declare () {
        Final >>= statement {pattern {first (Exp)}};
        Exp = rest (Exp);
    }

    void parser::define () {
        Final >>= statement {pattern {first (rest (Exp))}, first (Exp)};
        Exp = rest (rest (Exp));
    }

    template <typename X>
    expression zoob (data::string_view z) {
        // note: we don't check whether the * operation worked because
        // it should always work.
        return leaf<X>::make (*data::encoding::read<X> {} (z));
    }

    expression number_parser::result () {

        if (!SuffixFlag) {
            if (data::encoding::decimal::valid (Value))
                return natural::make (data::N {Value});
            else return call::make (symbol::make ("scriptnum"),
            {bytes::make (Bitcoin::integer::read (Value))});
        }

        if (!bool (Fixed)) {
            if (Endian) throw data::exception {} << "No endianness for unbounded number types.";
            if (data::encoding::decimal::valid (Value)) {
                if (UnsignedFlag) return natural::make (data::N {Value});
                else return integer::make (data::Z {Value});
            } else {
                if (UnsignedFlag)
                    throw data::exception {} << "No unsigned scriptnum type";
                else return call::make (symbol::make ("scriptnum"),
                {bytes::make (Bitcoin::integer::read (Value))});
            }
        }

        if (*Fixed == 8) {
            if (UnsignedFlag) return zoob<data::byte> (Value);
            else return zoob<data::int8> (Value);
        } else if (*Fixed == 16) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint16_little> (Value);
                    else return zoob<data::int16_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint16_big> (Value);
                    else return zoob<data::int16_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint16> (Value);
                else return zoob<data::int16> (Value);
            }
        } else if (*Fixed == 32) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint32_little> (Value);
                    else return zoob<data::int32_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint32_big> (Value);
                    else return zoob<data::int32_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint32> (Value);
                else return zoob<data::int32> (Value);
            }
        } else if (*Fixed == 64) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint64_little> (Value);
                    else return zoob<data::int64_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint64_big> (Value);
                    else return zoob<data::int64_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint64> (Value);
                else return zoob<data::int64> (Value);
            }
        } else if (*Fixed == 128) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint128_little> (Value);
                    else return zoob<data::int128_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint128_big> (Value);
                    else return zoob<data::int128_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint128> (Value);
                else return zoob<data::int128> (Value);
            }
        } else if (*Fixed == 160) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint160_little> (Value);
                    else return zoob<data::int160_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint160_big> (Value);
                    else return zoob<data::int160_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint160> (Value);
                else return zoob<data::int160> (Value);
            }
        } else if (*Fixed == 224) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint224_little> (Value);
                    else return zoob<data::int224_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint224_big> (Value);
                    else return zoob<data::int224_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint224> (Value);
                else return zoob<data::int224> (Value);
            }
        } else if (*Fixed == 256) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint256_little> (Value);
                    else return zoob<data::int256_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint256_big> (Value);
                    else return zoob<data::int256_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint256> (Value);
                else return zoob<data::int256> (Value);
            }
        } else if (*Fixed == 320) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint320_little> (Value);
                    else return zoob<data::int320_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint320_big> (Value);
                    else return zoob<data::int320_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint320> (Value);
                else return zoob<data::int320> (Value);
            }
        } else if (*Fixed == 448) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint448_little> (Value);
                    else return zoob<data::int448_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint448_big> (Value);
                    else return zoob<data::int448_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint448> (Value);
                else return zoob<data::int448> (Value);
            }
        } else if (*Fixed == 512) {
            if (Endian) {
                if (*Endian == data::endian::little) {
                    if (UnsignedFlag) return zoob<data::uint512_little> (Value);
                    else return zoob<data::int512_little> (Value);
                } else {
                    if (UnsignedFlag) return zoob<data::uint512_big> (Value);
                    else return zoob<data::int512_big> (Value);
                }
            } else {
                if (UnsignedFlag) return zoob<data::uint512> (Value);
                else return zoob<data::int512> (Value);
            }
        } else throw data::exception {} << "Invalid fixed number size " << *Fixed;
    }

}
