#ifndef BITCOIN_CALCULATOR_OPERATORS
#define BITCOIN_CALCULATOR_OPERATORS

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
        call,
        unary,
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
        colon,
        is,
        condition,
        double_implication,
        intuitionistic_and,
        intuitionistic_or,
        intuitionistic_implies
    };

    constexpr const binary_operand max_precedence =
        binary_operand (data::byte (binary_operand::intuitionistic_implies) + 1);

    constexpr const char *binary_operator (binary_operand X) {
        switch (X) {
            case binary_operand::cat : return "<>";
            case binary_operand::power : return "^";
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
            case binary_operand::bit_and : return "&:";
            case binary_operand::bit_xor : return "^:";
            case binary_operand::bit_or : return "|:";
            case binary_operand::bool_equal : return "==";
            case binary_operand::bool_unequal : return "!=";
            case binary_operand::bool_and : return "&&";
            case binary_operand::bool_or : return "||";
            case binary_operand::equal : return "=";
            case binary_operand::unequal : return "/=";
            case binary_operand::identical : return "===";
            case binary_operand::is : return ":-";
            case binary_operand::condition : return "/;";
            case binary_operand::double_implication : return "<==>";
            case binary_operand::intuitionistic_and : return "&";
            case binary_operand::intuitionistic_or : return "|";
            case binary_operand::intuitionistic_implies : return "=>";
            default : return "";
        }
    }

}

#endif

