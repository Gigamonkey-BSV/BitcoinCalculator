#include <Diophant/parse.hpp>
#include <Diophant/values/leaf.hpp>
#include <Diophant/values/lambda.hpp>
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
    void test_eval (std::string input, bool expect_eval = true);
    void test_eval (std::string input, std::string expect_eval);

    expression make_natural (data::N n) {
        return natural::make (n);
    }

    expression make_integer (data::Z n) {
        return integer::make (n);
    }

    expression make_secret (data::uint256 u) {
        return call::make (symbol::make ("secret"), {uint256::make (u)});
    }

    expression make_scriptnum (const std::string &x) {
        return call::make (symbol::make ("scriptnum"),
            {bytes::make (Bitcoin::integer::read (x))});
    }

    expression unary (char x, expression e) {
        return unop::make (unary_operand {x}, e);
    }

    template <typename ... ops>
    expression binary (binary_operand op, ops... bbbb) {
        return binop::make (op, data::stack<expression> {bbbb...});
    }

    expression True () {
        return boolean::make (true);
    }

    expression False () {
        return boolean::make (false);
    }

    expression And (expression a, expression b) {
        return binop::make (binary_operand::bool_and, a, b);
    }

    expression Or (expression a, expression b) {
        return binop::make (binary_operand::bool_or, a, b);
    }

    expression Plus (expression a, expression b) {
        return binop::make (binary_operand::plus, a, b);
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

        // call that doesn't evaluate to anything
        test_eval ("a b c d", call::make (symbol::make ("a"), {symbol::make ("b"), symbol::make ("c"), symbol::make ("d")}));
        test_eval ("f (a b)", call::make (symbol::make ("f"), {call::make (symbol::make ("a"), {symbol::make ("b")})}));

        test ("f");
        test ("f;");
        test ("f _a;");
        test ("f _a", false);
        test ("f _a := x");
        test ("f _a := x;");
        test ("f _a := x; y");

        // boolean
        test ("true", symbol::make ("true"), True ());
        test ("false", symbol::make ("false"), False ());

        test ("!true", unary ('!', symbol::make ("true")), False ());
        test ("!false", unary ('!', symbol::make ("false")), True ());

        test ("true && false", And (symbol::make ("true"), symbol::make ("false")), False ());
        test ("false && true", And (symbol::make ("false"), symbol::make ("true")), False ());

        test ("true || false", Or (symbol::make ("true"), symbol::make ("false")), True ());
        test ("false || true", Or (symbol::make ("false"), symbol::make ("true")), True ());

        // number formats.
        test ("0", make_natural (0), make_natural (0));
        test ("9876543", make_natural (9876543), make_natural (9876543));

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
        test ("'abcdef000001'", bytes::make (*data::encoding::hex::read ("abcdef000001")));
        test ("'abcdef00001'", false);

        // invalid hex number.
        test ("0x0", false);

        // hex numbers
        test ("0x", make_scriptnum ("0x"));
        test ("0x00", make_scriptnum ("0x00"));
        test ("0x80", make_scriptnum ("0x80"));
        test ("0x01", make_scriptnum ("0x01"));

        // lists
        test (R"([])", list::make ({}), list::make ({}));
        test (R"([x, 21, "hi"])");

        // string operations.

        // cat
        test_eval (R"("abcd" <> "efgh")", string::make ("abcdefgh"));
        test_eval (R"('00ff' <> 'abab')", bytes::make (*data::encoding::hex::read ("00ffabab")));

        // unary operators
        test ("!8", unary ('!', make_natural (8)));
        test ("8+", false);
        test ("8-", false);

        // bitnot
        test_eval ("~''", "''");
        test_eval ("~'00'", "'ff'");
        test_eval ("~'80'", "'7f'");

        test_eval ("~0x", "0x");
        test_eval ("~0x00", "0xff");
        test_eval ("~0x80", "0x7f");

        // negative zero
        test ("-0", unary ('-', make_natural (0)), make_integer (0));
        test ("- 0", unary ('-', make_natural (0)), make_integer (0));

        test ("-0x00", unary ('-', make_scriptnum ("0x00")), make_scriptnum ("0x"));
        test ("-0x", unary ('-', make_scriptnum ("0x")), make_scriptnum ("0x"));

        // arithmetic
        test ("0 + 0");
        test ("1 + 0");
        test ("1 + 1");

        test ("123 + 234", binary (binary_operand::plus, make_natural (123), make_natural (234)), make_natural (357));

        test_eval ("0x80 == 0x00", "0x");
        test_eval ("0x81 == 0x8001", "0x");

        // these should both have a divide by zero error on evaluation.
        test ("1 / 0");
        test ("1 % 0");

        // coordinates and secrets
        test_eval ("-secret 1", "secret 115792089237316195423570985008687907852837564279074904382605163141518161494336");

        test_eval ("-coord 1", "coord 115792089237316195423570985008687907853269984665640564039457584007908834671662");

        test_eval ("coord 1 + coord 2", "coord 3");
        test_eval ("secret 1 + secret 2", "secret 3");

        // valid and invalid secret keys
        test_eval ("valid (secret 1)", True ());
        test_eval ("valid (secret 0)", False ());

        test_eval ("to_public true (secret 123)", "03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");
        test_eval ("to_public false (secret 123)",
            "04cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe3252342dbd5610983c1877f7668b2664196453c29169c6b9182de10feddd82f09b915");

        test_eval ("compress "
            "04cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe3252342dbd5610983c1877f7668b2664196453c29169c6b9182de10feddd82f09b915",
            "03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");

        test_eval (R"({x -> 3, y -> 5}.x)", make_natural (3));

        // base 58
        test_eval ("base58.encode 1234", R"("NH")");
        test_eval (R"(base58.decode "NH")", make_natural (1234));

        test_eval (R"(if 1 == 0 then hi else bye)", symbol::make ("bye"));
        test_eval (R"(if 0x81 == 0x8001 then hi else bye)", symbol::make ("hi"));

        test_eval (
            R"(verify (to_public false (secret 123)) (SHA2_256 "Hola, babe!") )"
            R"('3045022100f0787177bfbd3766eb24bd92872eee4206b1c52a8c9de9e74e7ddad0ce6c1)"
            R"(57e0220080600a667bb7d1e601cc1f4efa244c0269a3bca18b8eac9c30b4ee3f1beab36')", True ());

        // addresses


        // WIFs

        // HD
/*
        // @ f -> let g -> @ x -> f (x x) in g g $ @ f n -> if n == 0 then 1 else n * f (n - 1) $ 5
        //
        // (@ f -> let g -> @ x -> f (x x) in g g) (@ f n -> if n == 0 then 1 else n * f (n - 1)) 5
        //
        // let g -> @ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) (x x) in g g $ 5
        //
        // ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) (x x))
        //     (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) (x x))) $ 5
        //
        // @ f n -> if n == 0 then 1 else n * f (n - 1) $
        //     ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) (x x))
        //         (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) (x x))) $ 5
        //
        // if 5 == 0 then 1 else 5 * ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //     (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))) (5 - 1)
        //
        // 5 * ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //     (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))) (5 - 1)
        //
        // 5 * (@ f n -> if n == 0 then 1 else n * f (n - 1) $
        //     ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //         (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x)))) (5 - 1)
        //
        // 5 * (@ f n -> if n == 0 then 1 else n * f (n - 1) $
        //     ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //         (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x)))) 4
        //
        // 5 * (if 4 == 0 then 1 else 4 * ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //         (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))) (4 - 1)
        //
        // 5 * 4 * ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //         (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))) (4 - 1)
        //
        // 5 * 4 * @ f n -> if n == 0 then 1 else n * f (n - 1) $
        //     ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //         (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))) $ (4 - 1)
        //
        // 5 * 4 * @ f n -> if n == 0 then 1 else n * f (n - 1) $
        //     ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //         (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))) $ 3
        //
        // 5 * 4 * if 3 == 0 then 1 else 3 * ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //     (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))) (3 - 1)
        //
        // 5 * 4 * 3 * ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //     (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))) (3 - 1)
        //
        // 5 * 4 * 3 * (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $
        //     ((@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x))
        //         (@ x -> @ f n -> if n == 0 then 1 else n * f (n - 1) $ (x x)))) (3 - 1)
        test ("@ f -> let g -> @ x -> f (x x) in g g $ @ f n -> if n == 0 then 1 else n * f (n - 1) $ 5",
            binary (binary_operand::apply,
                lambda::make ({symbol {"f"}},
                    let::make (
                        {{symbol {"g"}, lambda::make (
                            {symbol {"x"}},
                            call::make (symbol::make ("f"), {call::make (symbol::make ("x"), {symbol::make ("x")})}))}},
                        call::make (symbol::make ("g"), {symbol::make ("g")}))),
                lambda::make ({symbol {"f"}, symbol {"n"}}, dif::make (
                    binary (binary_operand::bool_equal, symbol::make ("n"), make_secret (0)),
                    make_secret (1),
                    binary (binary_operand::times, symbol::make ("n"),
                        call::make (symbol::make ("f"), {binary (binary_operand::minus, symbol::make ("n"), make_secret (1))})))),
                make_secret (5)),
            make_secret (120));*/

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
        EXPECT_NO_THROW (ex = read_line (input).first ().Predicate) << "testing input " << input;
        EXPECT_EQ (ex, expect_read) << "testing input " << input << "; expected " << ex << " == " << expect_read;
        return ex;
    }

    // test whether the exression will be read as a particular expression.
    void test (std::string input, expression expect_read) {
        test_parse (input, expect_read);
    }

    // test whether the expression will evaluate to a given expression.
    void test (std::string input, expression expect_read, expression expect_eval) {
        expression ex = m.evaluate (test_parse (input, expect_read));
        EXPECT_EQ (ex, expect_eval) << "expected " << input << " to evaluate to " << expect_eval << " but got " << ex;
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
        auto n = read_line (input);
        if (expect_eval) {
            EXPECT_NO_THROW (m.evaluate (n));
        } else {
            EXPECT_THROW (m.evaluate (n), data::exception);
        }
    }

    void test_eval (std::string input, expression expect_eval) {
        auto [mm, ex] = m.evaluate (read_line (input));
        EXPECT_EQ (ex, expect_eval) << "expected " << input << " to evaluate to " << expect_eval;
    }

    void test_eval (std::string input, std::string expect_eval) {
        EXPECT_EQ (m.evaluate (read_line (input)).Expression, read_expression (expect_eval)) << "expected " << input << " to evaluate to " << expect_eval;
    }

}

