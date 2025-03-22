#include <parse.hpp>
#include <value.hpp>
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

    expression make_secret (uint256 u) {
        return secret::make (secp256k1::secret {uint256 {u}});
    }

    expression make_scriptnum (const Bitcoin::integer &x) {
        return scriptnum::make (x);
    }

    expression unary (char x, expression e) {
        return unary_operation::make (unary_operand {x}, e);
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

        // nil
        test ("", expression {}, expression {});
        test (" ", expression {});
        test ("()", expression {});
        test ("( )", expression {});
        test (" ( ) ", expression {});
        test (" ( () ) ", expression {});
        test (" ( (()) ) ", expression {});
        test ("nil", symbol::make ("nil"), expression {});

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

        // hex numbers
        test ("0x", make_scriptnum ("0x"));
        test ("0x00", make_scriptnum ("0x00"));
        test ("0x80", make_scriptnum ("0x80"));
        test ("0x01", make_scriptnum ("0x01"));

        // invalid hex number.
        test ("0x0", false);

        // invalid pubkeys
        test ("023456", false);
        test ("034567", false);
        test ("045678", false);

        // hex strings
        test ("'abcdef000001'");
        test ("'abcdef00001'", false);

        // unary operators
        test ("-0", make_secret (0), make_secret (0));
        test ("- 0", make_secret (0), make_secret (0));

        test ("-0x00", make_scriptnum ("0x00"), make_scriptnum ("0x80"));
        test ("-0x", make_scriptnum ("0x"), make_scriptnum ("0x80"));

        // cat
        test (R"("abcd" <> "efgh")", string::make ("abcdefgh"));

        test ("0 + 0");
        test ("1 + 0");
        test ("1 + 1");
        test ("-1", unary ('-', make_secret (1)),
            make_secret (uint256::read ("115792089237316195423570985008687907852837564279074904382605163141518161494336")));

        // these should both have a divide by zero error on evaluation.
        test ("1 / 0");
        test ("1 % 0");

        test ("!8", unary ('!', make_secret (8)));
        test ("8+", false);
        test ("8-", false);

        // negative zero
        test ("-0x");

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
        EXPECT_NO_THROW (ex = read_line (input));
        EXPECT_EQ (ex, expect_read);
        return ex;
    }

    // test whether the exression will be read as a particular expression.
    void test (std::string input, expression expect_read) {
        test_parse (input, expect_read);
    }

    // test whether the expression will evaluate to a given expression.
    void test (std::string input, expression expect_read, expression expect_eval) {
        expression ex = m.evaluate (test_parse (input, expect_read));
        EXPECT_EQ (ex, expect_eval);
    }

    void test (std::string input, expression expect_read, bool expect_eval) {
        expression ex = test_parse (input, expect_read);
        if (expect_eval) {
            EXPECT_NO_THROW (m.evaluate (ex));
        } else {
            EXPECT_THROW (m.evaluate (ex), data::exception);
        }
    }

}

