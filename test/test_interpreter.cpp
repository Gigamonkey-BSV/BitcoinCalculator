#include <parse.hpp>
#include <value.hpp>
#include "gtest/gtest.h"

namespace Diophant {

    // test whether the parser will accept the given string.
    void test (std::string input, bool expect_success = true);

    // test whether the exression will be read as a particular expression.
    void test (std::string input, expression expect_read, bool expect_equal = true);

    // test whether the expression will evaluate to a given expression.
    void test (std::string input, expression expected_read, expression expect_eval, bool expect_equal = true);

    expression make_secret (uint256 u) {
        return secret::make (secp256k1::secret {uint256 {u}});
    }

    expression unary (char x, expression e) {
        return unary_operation::make (unary_operator {x}, e);
    }

    expression True () {
        return scriptnum::make (1);
    }

    expression False () {
        return scriptnum::make (0);
    }

    expression And (expression, expression);
    expression Or (expression, expression);
    expression Plus (expression, expression);

    TEST (ParseTest, TestParse) {

        // nil
        test ("", expression {}, expression {});
        test (" ", expression {});
        test ("()", expression {});
        test ("( )", expression {});
        test (" ( ) ", expression {});
        test (" ( () ) ", expression {});
        test (" ( (()) ) ", expression {});
        test ("Nil", symbol::make ("Nil"), expression {});

        // unmatched parentheses
        test ("(", false);
        test (")", false);
        test ("(()", false);
        test (")()", false);
        test ("())", false);
        test ("()(", false);

        // boolean
        test ("True", symbol::make ("True"), True ());
        test ("False", symbol::make ("False"), False ());

        test ("!True", unary ('!', symbol::make ("True")), False ());
        test ("!False", unary ('!', symbol::make ("False")), True ());

        test ("True && False", And (symbol::make ("True"), symbol::make ("False")), False ());
        test ("False && True", And (symbol::make ("False"), symbol::make ("True")), False ());

        test ("True || False", Or (symbol::make ("True"), symbol::make ("False")), True ());
        test ("False || True", Or (symbol::make ("False"), symbol::make ("True")), True ());

        test ("0", make_secret (0), make_secret (0));
        test ("-0", make_secret (0), make_secret (0));
        test ("- 0", make_secret (0), make_secret (0));

        test ("0 + 0");
        test ("1 + 0");
        test ("1 + 1");
        test ("-1", unary ('-', make_secret (1)),
            make_secret (uint256::read ("115792089237316195423570985008687907852837564279074904382605163141518161494336")));

        // these should both have a divide by zero error on evaluation.
        test ("1 / 0");
        test ("1 % 0");

        test ("+8", unary ('!', make_secret (8)));
        test ("8+", false);
        test ("8-", false);

        // invalid dec number
        test ("0923", false);

        test ("0x");

        // invalid hex number.
        test ("0x0", false);

        test ("x");
        test ("x123");

        // hex strings
        test ("'abcdef000001'");
        test ("'abcdef00001'", false);

        // invalid pubkeys
        test ("023456", false);
        test ("034567", false);
        test ("045678", false);

    }

    machine m = initialize ();

    // test whether the parser will accept the given string.
    void test (std::string input, bool expect_success) {
        if (expect_success) {
            EXPECT_THROW (read_line (input), parse_error);
        } else {
            EXPECT_NO_THROW (read_line (input));
        }
    }

    expression test_parse (std::string input, expression expect_read) {
        expression ex = read_line (input);
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

