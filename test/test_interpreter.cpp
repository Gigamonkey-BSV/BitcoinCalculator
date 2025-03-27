#include <parse.hpp>
#include <values/leaf.hpp>
#include "gtest/gtest.h"

namespace Diophant {

    machine m;

    // test whether the parser will accept the given string.
    void test (std::string input, bool expect_success = true);

    // test whether the exression will be read as a particular expression.
    void test (std::string input, expression expect_read);

    // test whether the expression will evaluate to a given expression.
    void test (std::string input, expression expected_read, expression expect_eval);

    // test whether the expression will error when evaluated.
    void test (std::string input, expression expected_read, bool expect_eval);

    // test whether the expression evaluates to the given expression or throws an error.
    void test_eval (std::string input, expression expect_eval);
    void test_eval (std::string input, bool expect_eval);

    expression make_secret (uint256 u) {
        return secret::make (secp256k1::secret {uint256 {u}});
    }

    expression make_scriptnum (const std::string &x) {
        return scriptnum::make (Bitcoin::integer {x});
    }

    expression unary (char x, expression e) {
        return unary_operation::make (unary_operand {x}, e);
    }

    expression binary (binary_operand op, expression left, expression right) {
        return binary_operation::make (op, left, right);
    }

    expression True () {
        return scriptnum::make (1);
    }

    expression False () {
        return scriptnum::make (0);
    }

    expression And (expression a, expression b) {
        return binary_operation::make (binary_operand::bool_and, a, b);
    }

    expression Or (expression a, expression b) {
        return binary_operation::make (binary_operand::bool_or, a, b);
    }

    expression Plus (expression a, expression b) {
        return binary_operation::make (binary_operand::plus, a, b);
    }

    TEST (InterpreterTest, TestInterpreter) {

        m = initialize ();

        test ("", nil::make (), nil::make ());
        test (" ", nil::make ());
        test ("()", nil::make ());
        test ("( )", nil::make ());
        test (" ( ) ", nil::make ());
        test (" ( () ) ", nil::make ());
        test (" ( (()) ) ", nil::make ());
        test ("nil", symbol::make ("nil"), nil::make ());

        // unmatched parentheses
        test ("(", false);
        test (")", false);
        test ("(()", false);
        test (")()", false);
        test ("())", false);
        test ("()(", false);
        test ("[", false);
        test ("]", false);
        test ("[(])", false);

        // empty string
        test (R"("")");
        test (R"("abcd")");
        test (R"("_x2")");
        test (R"("202")");
        test (R"("xyz\")", false);

        // symbols
        test ("x", symbol::make ("x"), symbol::make ("x"));
        test ("x123");

        // boolean
        test ("True", symbol::make ("True"), True ());
        test ("False", symbol::make ("False"), False ());

        test ("!True", unary ('!', symbol::make ("True")), False ());
        test ("!False", unary ('!', symbol::make ("False")), True ());

        test ("True && False", And (symbol::make ("True"), symbol::make ("False")), False ());
        test ("False && True", And (symbol::make ("False"), symbol::make ("True")), False ());

        test ("True || False", Or (symbol::make ("True"), symbol::make ("False")), True ());
        test ("False || True", Or (symbol::make ("False"), symbol::make ("True")), True ());

        // number formats.
        test ("0", make_secret (0), make_secret (0));
        test ("9876543", make_secret (9876543), make_secret (9876543));

        // invalid dec number
        test ("0923", false);

        // valid pubkeys
        test ("02cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");
        test ("03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");
        test ("04cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523"
                "42dbd5610983c1877f7668b2664196453c29169c6b9182de10feddd82f09b915");

        // invalid pubkeys
        test ("023456", false);
        test ("034567", false);
        test ("045678", false);

        // hex strings
        test ("'abcdef000001'");
        test ("'abcdef00001'", false);

        // hex numbers
        test ("0x", make_scriptnum ("0x"));
        test ("0x00", make_scriptnum ("0x00"));
        test ("0x80", make_scriptnum ("0x80"));
        test ("0x01", make_scriptnum ("0x01"));

        // invalid hex number.
        test ("0x0", false);

        // unary operators
        test ("-0", unary ('-', make_secret (0)), make_secret (0));
        test ("- 0", unary ('-', make_secret (0)), make_secret (0));

        test ("!8", unary ('!', make_secret (8)));
        test ("8+", false);
        test ("8-", false);

        // negative zero
        test ("-0x00", unary ('-', make_scriptnum ("0x00")), make_scriptnum ("0x"));
        test ("-0x", unary ('-', make_scriptnum ("0x")), make_scriptnum ("0x"));

        // bitnot

        // string cat
        test (R"("abcd" <> "efgh")", string::make ("abcdefgh"));

        // scriptnum cat

        // arithmetic with secrets
        test ("-1", unary ('-', make_secret (1)),
            make_secret (uint256::read ("115792089237316195423570985008687907852837564279074904382605163141518161494336")));
        test ("0 + 0");
        test ("1 + 0");
        test ("1 + 1");

        test ("123 + 234", binary (binary_operand::plus, make_secret (123), make_secret (234)), make_secret (357));

        // these should both have a divide by zero error on evaluation.
        test ("1 / 0");
        test ("1 % 0");

        // base 58
        test_eval ("Base58Encode 1234", string::make ("NH"));
        test_eval (R"(Base58Decode "NH")", make_secret (1234));

        // TODO an undefined function seems to go into an infinite loop.

    }

    // test whether the parser will accept the given string.
    void test (std::string input, bool expect_success) {
        if (expect_success) {
            EXPECT_NO_THROW (read_line (input));
        } else {
            EXPECT_THROW (read_line (input), parse_error);
        }
    }

    expression test_parse (std::string input, expression expect_read) {
        expression ex;
        EXPECT_NO_THROW (ex = read_line (input)) << "testing input " << input;
        EXPECT_EQ (ex, expect_read) << "testing input " << input;
        return ex;
    }

    // test whether the exression will be read as a particular expression.
    void test (std::string input, expression expect_read) {
        test_parse (input, expect_read);
    }

    // test whether the expression will evaluate to a given expression.
    void test (std::string input, expression expect_read, expression expect_eval) {
        expression ex = m.evaluate (test_parse (input, expect_read));
        EXPECT_EQ (ex, expect_eval) << "expected " << input << " to evaluate to " << expect_eval;
    }

    void test (std::string input, expression expect_read, bool expect_eval) {
        expression ex = test_parse (input, expect_read);
        if (expect_eval) {
            EXPECT_NO_THROW (m.evaluate (ex));
        } else {
            EXPECT_THROW (m.evaluate (ex), data::exception);
        }
    }

    void test_eval (std::string input, bool expect_eval) {
        expression ex = read_line (input);
        if (expect_eval) {
            EXPECT_NO_THROW (m.evaluate (ex));
        } else {
            EXPECT_THROW (m.evaluate (ex), data::exception);
        }
    }

    void test_eval (std::string input, expression expect_eval) {
        expression ex = m.evaluate (read_line (input));
        EXPECT_EQ (ex, expect_eval) << "expected " << input << " to evaluate to " << expect_eval;
    }

}

