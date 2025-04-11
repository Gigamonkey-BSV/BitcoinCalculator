#ifndef BITCOIN_CALCULATOR_OPERATORS
#define BITCOIN_CALCULATOR_OPERATORS

#include <iostream>

namespace Diophant {

    enum class unary_operand : char {
        tilda = '~',
        plus =  '+',
        negate = '-',
        star = '*',
        ampersand = '&',
        bool_not = '!'
    };

    enum class binary_operand : data::byte {
        unary,
        call,
        dot,
        cat,
        power,
        times,
        divide,
        mod,
        divmod,
        plus,
        minus,
        greater,
        less,
        greater_equal,
        less_equal,
        bool_equal,
        bool_unequal,
        bit_and,
        bit_xor,
        bit_or,
        bit_nand,
        bit_nor,
        bool_and,         // &&
        bool_or,          // ||
        equal,
        unequal,
        identical,        // ===
        apply,
        element,
        colon,
        such_that,
        double_implication,
        intuitionistic_and,
        intuitionistic_or,
        intuitionistic_implies
    };

    using precedence = binary_operand;

    constexpr const precedence max_precedence =
        precedence (data::byte (binary_operand::intuitionistic_implies) + 1);

    constexpr const char *binary_operator (binary_operand X);

    std::ostream &operator << (std::ostream &, unary_operand);
    std::ostream &operator << (std::ostream &, binary_operand);

    constexpr const char *binary_operator (binary_operand X) {
        switch (X) {
            case binary_operand::dot : return ".";
            case binary_operand::cat : return "<>";
            case binary_operand::power : return "^^";
            case binary_operand::times : return "*";
            case binary_operand::divide : return "/";
            case binary_operand::mod : return "%";
            case binary_operand::divmod : return "/%";
            case binary_operand::plus : return "+";
            case binary_operand::minus : return "-";
            case binary_operand::greater_equal : return ">";
            case binary_operand::less_equal : return "<=";
            case binary_operand::greater : return ">";
            case binary_operand::less : return "<";
            case binary_operand::bit_and : return "&;";
            case binary_operand::bit_xor : return "^;";
            case binary_operand::bit_or : return "|;";
            case binary_operand::bool_equal : return "==";
            case binary_operand::bool_unequal : return "!=";
            case binary_operand::bool_and : return "&&";
            case binary_operand::bool_or : return "||";
            case binary_operand::equal : return "=";
            case binary_operand::unequal : return "/=";
            case binary_operand::identical : return "===";
            case binary_operand::apply : return "$";
            case binary_operand::element : return "-:";
            case binary_operand::such_that : return "/;";
            case binary_operand::double_implication : return "<==>";
            case binary_operand::intuitionistic_and : return "^";
            case binary_operand::intuitionistic_or : return "|";
            case binary_operand::intuitionistic_implies : return "=>";
            default : return "";
        }
    }

    constexpr bool inline is_associative (binary_operand x) {
        return x != binary_operand::element && x >= binary_operand::dot && (x <= binary_operand::times || x > binary_operand::divmod);
    }

    std::ostream inline &operator << (std::ostream &o, unary_operand u) {
        return o << char (u);
    }

    std::ostream inline &operator << (std::ostream &o, binary_operand b) {
        return o << binary_operator (b);
    }

}

#endif

