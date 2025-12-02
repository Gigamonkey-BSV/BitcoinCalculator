#include <Diophant/parse/parser.hpp>
#include <Diophant/values/leaf.hpp>
#include <Diophant/values/lambda.hpp>
#include "gtest/gtest.h"

namespace Diophant {

    expression make_byte (data::byte b) {
        return uint8::make (b);
    }

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

    class Interpreter : public ::testing::Test {
    protected:
        static machine Machine;

        // Runs once before *any* test in this suite runs.
        static void SetUpTestSuite () {}

        // Runs once after *all* tests in this suite finish.
        static void TearDownTestSuite () {}

        // test whether the parser will accept the given string.
        static void test (std::string input, bool expect_success = true);

        // test whether the exression will be read as a particular expression.
        static void test (std::string input, expression expect_read);

        // test whether the expression will evaluate to a given expression.
        static void test (std::string input, expression expected_read, expression expect_eval);

        // test whether the expression will error when evaluated.
        static void test (std::string input, expression expected_read, bool expect_eval);

        // test whether the expression evaluates to the given expression or throws an error.
        static void test_eval (std::string input, expression expect_eval);
        static void test_eval (std::string input, bool expect_eval = true);
        static void test_eval (std::string input, std::string expect_eval);
        static void test_eval (std::string input, const char *expect_eval);

        // we expect an error to be thrown.
        static void test_error (std::string input) {
            test_eval (input, false);
        }
    };

    machine Interpreter::Machine = initialize ();

    TEST_F (Interpreter, UnmatchedBrackets) {

        // unmatched parentheses
        test_error ("(");
        test_error (")");
        test_error ("(()");
        test_error (")()");
        test_error ("())");
        test_error ("()(");
        test_error ("[");
        test_error ("]");
        test_error ("[(])");

    }

    TEST_F (Interpreter, Nil) {

        // expressions that evaluate to nil
        test ("", nil::make (), nil::make ());
        test (" ", nil::make ());
        test ("()", nil::make ());
        test ("( )", nil::make ());
        test (" ( ) ", nil::make ());
        test (" ( () ) ", nil::make ());
        test (" ( (()) ) ", nil::make ());
        test ("nil", symbol::make ("nil"), nil::make ());
    }

    TEST_F (Interpreter, Call) {

        // symbols
        test ("x", symbol::make ("x"), symbol::make ("x"));
        test_eval ("x := 2");
        test_eval ("x123 := 2");
        test_error ("123 := 3");

        // call that doesn't evaluate to anything
        test_eval ("a b c d", call::make (symbol::make ("a"), {symbol::make ("b"), symbol::make ("c"), symbol::make ("d")}));
        test_eval ("f (a b)", call::make (symbol::make ("f"), {call::make (symbol::make ("a"), {symbol::make ("b")})}));

        test ("f");
        test ("f;");
        test ("f _a;");
        test_error ("f _a");
        test ("f _a := x");
        test ("f _a := x;");
        test ("f _a := x; y");
    }

    TEST_F (Interpreter, Constructs) {

        // lists
        test (R"([])", list::make ({}), list::make ({}));
        test (R"([x, 21, "hi"])");
        test_eval (R"([x, 21, "hi"].1)", "21");

        // structs
        test_eval (R"({x -> 3, y -> 5}.x)", "3");

        // lambda
        test_eval ("(@ x y -> y x) a b", "b a");
        test_eval ("@ x y -> y x $ a $ b", "b a");
    }

    TEST_F (Interpreter, Bool) {

        // boolean
        test ("true", symbol::make ("true"), True ());
        test ("false", symbol::make ("false"), False ());

        test ("!true", unary ('!', symbol::make ("true")), False ());
        test ("!false", unary ('!', symbol::make ("false")), True ());

        test ("true && false", And (symbol::make ("true"), symbol::make ("false")), False ());
        test ("false && true", And (symbol::make ("false"), symbol::make ("true")), False ());

        test ("true || false", Or (symbol::make ("true"), symbol::make ("false")), True ());
        test ("false || true", Or (symbol::make ("false"), symbol::make ("true")), True ());

        test_eval ("true == false", False ());
        test_eval ("false == true", False ());

        test_eval ("true == true", True ());
        test_eval ("false == false", True ());
    }

    TEST_F (Interpreter, Identical) {

        test_eval ("nil === nil", "true");
        //test_eval ("nil =!= nil", "false");
        test_eval ("true === true", "true");
        //test_eval ("true =!= true", "false");
        test_eval ("true === false", "false");
        //test_eval ("true =!= false", "true");
        test_eval ("230 === 230", "true");
        //test_eval ("345 =!= 123", "true");
        //test_eval ("0x0000 =!= 0x", "true");
        test_eval ("0x0000 == 0x", "true");
        test_eval ("X == X", "true");
        test_eval ("X != X", "false");

        test_eval (
            "04cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe3252342dbd5610983c1877f7668b2664196453c29169c6b9182de10feddd82f09b915"
            " == 03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523", "true");

        test_eval (
            "04cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe3252342dbd5610983c1877f7668b2664196453c29169c6b9182de10feddd82f09b915"
            " === 03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523", "false");

        // NOTE: it is an error to add a definition to ===, =!=, or !=
    }

    TEST_F (Interpreter, Scriptnum) {

        // invalid hex number.
        test_error ("0x0");

        // hex numbers
        test ("0x", make_scriptnum ("0x"));
        test ("0x00", make_scriptnum ("0x00"));
        test ("0x80", make_scriptnum ("0x80"));
        test ("0x01", make_scriptnum ("0x01"));

        // negative zero
        test ("-0x00", unary ('-', make_scriptnum ("0x00")), make_scriptnum ("0x"));
        test ("-0x", unary ('-', make_scriptnum ("0x")), make_scriptnum ("0x"));

        // equal versus identical
        test_eval ("0x80 == 0x00", "true");
        test_eval ("0x80 === 0x00", "false");

        test_eval ("0x81 == 0x8001", "true");
        test_eval ("0x81 === 0x8001", "false");

        // divide by zero should throw
        test_error ("0x01 / 0x");
        test_error (R"(0x01 % 0x)");
    }

    TEST_F (Interpreter, ScriptnumBool) {

        // cast to bool
        test_eval ("bool 0x", "false");
        test_eval ("bool 0x00", "false");
        test_eval ("bool 0x80", "false");
        test_eval ("bool 0x01", "true");
        test_eval ("bool 0x81", "true");

        test_eval ("scriptnum false", "0x");
        test_eval ("scriptnum true", "0x01");
    }

    TEST_F (Interpreter, ScriptnumN) {

        // cast to scriptnum and Z.
        test_eval ("scriptnum 0", "0x");
        test_eval ("scriptnum 1", "0x01");
        test_eval ("scriptnum (-1)", "0x81");
        test_eval ("Z 0x", "Z 0");
        test_eval ("Z 0x01", "Z 1");
        test_eval ("Z 0x80", "Z 0");
        test_eval ("Z 0x81", "-1");
        test_eval ("N 0x", "0");
        test_eval ("N 0x01", "1");
        test_eval ("N 0x80", "0");
        test_error ("N 0x81");
    }

    TEST_F (Interpreter, If) {

        // if
        test_eval (R"(if 1 == 0 then hi else bye)", symbol::make ("bye"));
        test_eval (R"(if 0x81 == 0x8001 then hi else bye)", symbol::make ("hi"));
    }

    TEST_F (Interpreter, String) {

        // string operations.

        // cat
        test_eval (R"("abcd" <> "efgh")", string::make ("abcdefgh"));
        test_eval (R"('00ff' <> 'abab')", bytes::make (*data::encoding::hex::read ("00ffabab")));

        test_eval (R"(cat "abcd" "efgh")", string::make ("abcdefgh"));
        test_eval (R"(cat '00ff' 'abab')", bytes::make (*data::encoding::hex::read ("00ffabab")));

        test_eval (R"(size "")", "0");
        test_eval (R"(size "abcd")", "4");
        test_eval (R"(size '')", "0");
        test_eval (R"(size 'abcd')", "2");

        // left, right
        test_eval (R"(left "" 0)", R"("")");
        test_error (R"(left "" 1)");
        test_eval (R"(left "ab" 0)", R"("")");
        test_eval (R"(left "ab" 1)", R"("a")");

        test_eval (R"(left '' 0x)", R"('')");
        test_error (R"(left '' 0x01)");
        test_eval (R"(left '1234' 0)", R"('')");
        test_eval (R"(left '1234' 1)", R"('12')");

        test_eval (R"(right "" 0)", R"("")");
        test_error (R"(right "" 1)");
        test_eval (R"(right "ab" 0)", R"("")");
        test_eval (R"(right "ab" 1)", R"("b")");

        test_eval (R"(right '' 0x)", R"('')");
        test_error (R"(right '' 0x01)");
        test_eval (R"(right '1234' 0)", R"('')");
        test_eval (R"(right '1234' 1)", R"('34')");

        // split
        test_eval (R"(split "" 0)", R"(["", ""])");
        test_eval (R"(split '' 0)", R"(['', ''])");
        test_error (R"(split "" 1)");
        test_eval (R"(split "ab" 0)", R"(["", "ab"])");
        test_eval (R"(split '1234' 0)", R"(['', '1234'])");
        test_eval (R"(split "ab" 1)", R"(["a", "b"])");
        test_eval (R"(split '1234' 1)", R"(['12', '34'])");

    }


    TEST_F (Interpreter, Types) {

        // the reason this and others fail is that
        // we don't evaluate the expression.
        //test_eval (R"(-2 :: Z)", "true");
        test_eval (R"(2 :: N)", "true");
        test_eval (R"("string" :: string)", "true");
        test_eval (R"("string" :: string | Z)", "true");
        //test_eval (R"(-5 :: string | Z)", "true");
        //test_eval (R"(true :: boolean)", "true");
        test_eval (R"(-2 :: string)", "false");
        test_eval (R"(2 :: boolean)", "false");
        test_eval (R"("string" :: N)", "false");
        test_eval (R"(true :: Z)", "false");
        //test_eval (R"(false :: string | Z)", "false");

        //test_eval (R"(-2 :> Z)");
        test_eval (R"(2 :> N)");
        test_eval (R"("string" :> string)");
        test_eval (R"("string" :> string | Z)");
        //test_eval (R"(-5 :> string | Z)");
        //test_eval (R"(true :> boolean)");
        test_error (R"(-2 :> string)");
        test_error (R"(2 :> boolean)");
        test_error (R"("string" :> N)");
        test_error (R"(true :> Z)");
        //test_error (R"(false :> string | Z)");
    }
/*
    TEST_F (Interpreter, Functions) {
        test_eval (R"(square x := x * x; [square 0, square 1, square -1, square 2, square -2, square "up"])",
            R"([0, 1, 1, 4, 4, "up" * "up"])");

        test_eval (R"(z x:N := x * x; [z 0, z 1, z 2, z "up"])", R"([0, 1, 4, z "up"])");

        test_eval (R"(double x:N := x * x; double x:string := x <> x; [double 0, double 1, double 2, double "up"])",
            R"([0, 1, 4, "upup"])");
    }

    TEST_F (Interpreter, Variables) {
        // error because x is an undefined variable.
        test_error ("x; x");
        // not an error because y is just a symbol.
        test_eval ("y");
        // error because y is a symbol.
        test_eval ("y := 2;");

        test_eval ("lever := on | off; is_on [_on] := true; is_on[_off] := false; lever -> bool :: is_on", "true");
    }*/

    TEST_F (Interpreter, Hash) {

        // hash functions
        test_eval ("SHA1_160 ''", "'da39a3ee5e6b4b0d3255bfef95601890afd80709'");
        test_eval ("SHA2_256 ''", "'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855'");
        test_eval ("RIPEMD_160 ''", "'9c1185a5c5e9fc54612808977ee8f548b2258d31'");
    }

    TEST_F (Interpreter, Keys) {

        // valid pubkeys
        test ("02cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");
        test ("03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");
        test ("04cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523"
                "42dbd5610983c1877f7668b2664196453c29169c6b9182de10feddd82f09b915");

        // invalid pubkeys
        test ("023456", false);
        test ("034567", false);
        test ("045678", false);

        // coordinates and secrets
        test_eval ("-secret 1", "secret 115792089237316195423570985008687907852837564279074904382605163141518161494336");

        test_eval ("-coord 1", "coord 115792089237316195423570985008687907853269984665640564039457584007908834671662");

        test_eval ("coord 1 + coord 2", "coord 3");
        test_eval ("secret 1 + secret 2", "secret 3");

        // valid and invalid secret keys
        test_eval ("valid (secret 1)", True ());
        test_eval ("valid (secret 0)", False ());

        // public keys
        test_eval ("to_public true (secret 123)", "03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");
        test_eval ("to_public false (secret 123)",
            "04cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe3252342dbd5610983c1877f7668b2664196453c29169c6b9182de10feddd82f09b915");

        test_eval ("compress "
            "04cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe3252342dbd5610983c1877f7668b2664196453c29169c6b9182de10feddd82f09b915",
            "03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");

        // castable to bytes
        test_eval ("bytes 03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523",
            "'03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523'");
        test_eval ("bytes (secret 345678)", "'4e46050000000000000000000000000000000000000000000000000000000000'");
        test_eval ("bytes (coord 456789)", "'55f8060000000000000000000000000000000000000000000000000000000000'");

        // verify signatures
        test_eval (
            R"(verify (to_public false (secret 123)) (SHA2_256 "Hola, babe!") )"
            R"('3045022100f0787177bfbd3766eb24bd92872eee4206b1c52a8c9de9e74e7ddad0ce6c1)"
            R"(57e0220080600a667bb7d1e601cc1f4efa244c0269a3bca18b8eac9c30b4ee3f1beab36')",
            True ());

        // TODO test sign

        // TODO test key algebra. I think there's something wrong with that.

    }

    TEST_F (Interpreter, Address) {

        // base 58
        test_eval ("base58.encode 1234", R"("NH")");
        test_eval (R"(base58.decode "NH")", "1234");

        // base 58 check.
        test_eval ("base58.check.encode [0_u8, 'abcdef000123']", R"("1AeqHaZrBsWzoXo")");
        test_eval (R"(base58.check.decode "1AeqHaZrBsWzoXo")", "[0_u8, 'abcdef000123']");

        // addresses
        test_eval ("address.encode [Hash160 (to_public true (secret 12345))]",
            R"("1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg")");

        test_eval ("address.encode [Hash160 (to_public true (secret 12345)), net.Main]",
            R"("1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg")");

        test_eval (R"(address.decode "1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg")",
            "[Hash160 (to_public true (secret 12345)), net.Main]");

        // address equal
        test_eval (R"((address [Hash160 (to_public true (secret 12345)), net.Main]) == (address "1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg"))",
            "true");

        test_eval (R"((address [Hash160 (to_public true (secret 12345))]) == (address "1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg"))",
            "true");

        // address to string
        test_eval (R"(string (address "1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg"))",
            R"("1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg")");

        test_eval (R"(string (address [Hash160 (to_public true (secret 12345)), net.Main]))",
            R"("1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg")");

        test_eval (R"(encode (address [Hash160 (to_public true (secret 12345)), net.Main]))",
            R"(address "1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg")");

        test_eval (R"(decode (address "1tto6zacx5cwTbZgUnDLnnRQWBFBvzoJg"))",
            R"(address [Hash160 (to_public true (secret 12345)), net.Main])");

        // WIF
        test_eval ("WIF.encode [secret 123, net.Main, true]",
            R"("L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ")");

        test_eval ("WIF.encode [secret 123, net.Main]",
            R"("L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ")");

        test_eval ("WIF.encode [secret 123]",
            R"("L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ")");

        // decode WIF
        test_eval (R"(WIF.decode "L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ")",
            R"([secret 123, net.Main, true])");

        // WIF to string
        test_eval (R"(string (WIF [secret 123, net.Main, true]))",
            R"("L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ")");

        test_eval (R"(string (WIF "L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ"))",
            R"("L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ")");

        // encode and decode WIF
        test_eval ("encode (WIF [secret 123, net.Main, true])",
            R"(WIF "L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ")");

        test_eval (R"(decode (WIF "L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ"))",
            R"(WIF ([secret 123, net.Main, true]))");

        // address from wif.
        test_eval (R"(address (WIF "L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ"))",
            R"(address "13EuEN7yHdxEB187aknyNuewMDNoFinXaw")");

        // TODO sign with WIF.

        // to_public with WIF
        test_eval (R"(to_public (WIF "L1LokMeMLVbnapboYCpeobZ67FkFBXKhYLMPs9mj7X4vk58AdCZQ"))",
            "03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");

        test_eval ("to_public (WIF [secret 123, net.Main, true])",
            "03cc45122542e88a92ea2e4266424a22e83292ff6a2bc17cdd7110f6d10fe32523");

        // the reason these don't work is that we don't yet evaluate or types.
/*
        // HD
        test_eval (R"(encode (HD.secret [secret 123, SHA2_256 "chain_code"]))",
            R"(HD.secret "xprv9s21ZrQH143K2e34Lcj9YiDRmzQ9wBaA2A7SkaLqvnvGn7qP92qUrfzjwx2mL1CeyJ7adN6AGq37a2Li6zMbAK1jS4YzWMQuaZAy8L9xAT1")");

        test_eval (R"(decode (HD.secret )"
            R"("xprv9s21ZrQH143K2e34Lcj9YiDRmzQ9wBaA2A7SkaLqvnvGn7qP92qUrfzjwx2mL1CeyJ7adN6AGq37a2Li6zMbAK1jS4YzWMQuaZAy8L9xAT1"))",
            R"(HD.secret [secret 123, SHA2_256 "chain_code"])");

        // to public with HD
        test_eval (
            R"(to_public (HD.secret "xprv9s21ZrQH143K2e34Lcj9YiDRmzQ9wBaA2A7SkaLqvnvGn7qP92qUrfzjwx2mL1CeyJ7adN6AGq37a2Li6zMbAK1jS4YzWMQuaZAy8L9xAT1"))"
            R"( == HD.pubkey (HD_encode_pubkey [to_public true (secret 123), SHA2_256 "chain_code"]))", "true");

        // to public

        test_eval (R"(string (HD.secret )"
            R"("xprv9s21ZrQH143K2e34Lcj9YiDRmzQ9wBaA2A7SkaLqvnvGn7qP92qUrfzjwx2mL1CeyJ7adN6AGq37a2Li6zMbAK1jS4YzWMQuaZAy8L9xAT1"))",
            R"("xprv9s21ZrQH143K2e34Lcj9YiDRmzQ9wBaA2A7SkaLqvnvGn7qP92qUrfzjwx2mL1CeyJ7adN6AGq37a2Li6zMbAK1jS4YzWMQuaZAy8L9xAT1")");

        test_eval (
            R"(string (to_public (HD.secret )"
            R"("xprv9s21ZrQH143K2e34Lcj9YiDRmzQ9wBaA2A7SkaLqvnvGn7qP92qUrfzjwx2mL1CeyJ7adN6AGq37a2Li6zMbAK1jS4YzWMQuaZAy8L9xAT1")))",
            R"("")");

        // TODO secret and pubkey from HD
        test_eval (R"(secret (HD.secret)"
            R"("xprv9s21ZrQH143K2e34Lcj9YiDRmzQ9wBaA2A7SkaLqvnvGn7qP92qUrfzjwx2mL1CeyJ7adN6AGq37a2Li6zMbAK1jS4YzWMQuaZAy8L9xAT1"))");

        test_eval (R"(pubkey (to_public (HD.secret)"
            R"("xprv9s21ZrQH143K2e34Lcj9YiDRmzQ9wBaA2A7SkaLqvnvGn7qP92qUrfzjwx2mL1CeyJ7adN6AGq37a2Li6zMbAK1jS4YzWMQuaZAy8L9xAT1")))");*/

        // TODO derivations

    }

    TEST_F (Interpreter, EverythingElse) {

        // number formats.
        test ("0", make_natural (0), make_natural (0));
        test ("9876543", make_natural (9876543), make_natural (9876543));

        // invalid dec number
        test_error ("0923");

        // strings
        test (R"("")");
        test (R"("abcd")");
        test (R"("_x2")");
        test (R"("202")");
        test_error (R"("xyz\")");

        // unary operators
        test ("!8", unary ('!', make_natural (8)));
        test_error ("8+");
        test_error ("8-");

        // negative zero
        test ("-0", unary ('-', make_natural (0)), make_integer (0));
        test ("- 0", unary ('-', make_natural (0)), make_integer (0));

        // arithmetic
        test_eval ("0x + 0x", "0x");
        test_eval ("0x01 + 0x", "0x01");
        test_eval ("0x01 + 0x01", "0x02");

        test_eval ("0 + 0", "0");
        test_eval ("1 + 0", "1");
        test_eval ("1 + 1", "2");
        test_eval ("2 * 2", "4");

        test ("123 + 234", binary (binary_operand::plus, make_natural (123), make_natural (234)), make_natural (357));

        // these should have a divide by zero error on evaluation.

        // TODO this is commented because in general the / operator should produce a rational number.
        // and we haven't implemented that yet.
        //test_error ("1 / 0");
        //test_error ("1 % 0");

        // bytes
        test_eval ("0_u8", make_byte (0));
        test ("0_u8 + 0_u8", "0_u8");
        test ("-1_u8", "255_u8");
        test ("255_u8 + 1_u8", "0_u8");

        // hex strings
        test ("'abcdef000001'", bytes::make (*data::encoding::hex::read ("abcdef000001")));
        test ("'abcdef00001'", false);

        test_eval ("'abcdef000001'.1", make_byte (0xcd));

        // bitnot
        test_eval ("~''", "''");
        test_eval ("~'00'", "'ff'");
        test_eval ("~'80'", "'7f'");

        test_eval ("~0x", "0x");
        test_eval ("~0x00", "0xff");
        test_eval ("~0x80", "0x7f");

/*
        // @ f -> let g -> @ x -> f (x x) in g g $ @ f n -> if n == 0 then 1 else n * f (n - 1) $ 5
        //
        // (@ f -> let g -> @ x j-> f (x x) in g g) (@ f n -> if n == 0 then 1 else n * f (n - 1)) 5
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
    void Interpreter::test (std::string input, bool expect_success) {
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
    void Interpreter::test (std::string input, expression expect_read) {
        test_parse (input, expect_read);
    }

    // test whether the expression will evaluate to a given expression.
    void Interpreter::test (std::string input, expression expect_read, expression expect_eval) {
        expression ex = Machine.evaluate (test_parse (input, expect_read));
        EXPECT_EQ (ex, expect_eval) << "expected " << input << " to evaluate to " << expect_eval << " but got " << ex;
    }

    void Interpreter::test (std::string input, expression expect_read, bool expect_eval) {
        expression ex = test_parse (input, expect_read);
        if (expect_eval) {
            EXPECT_NO_THROW (Machine.evaluate (ex));
        } else {
            EXPECT_THROW (Machine.evaluate (ex), data::exception);
        }
    }

    void Interpreter::test_eval (std::string input, bool expect_eval) {
        program n;
        try {
            n = read_line (input);
        } catch (const parse_error &p) {
            if (!expect_eval) return;
            FAIL () << "Expected " << input << " to evaluate to a Diophant expression.";
        }
        if (expect_eval) {
            EXPECT_NO_THROW (Machine.evaluate (n)) << "Expected " << input << " to throw no exception but it did.";
        } else {
            try {
                Machine.evaluate (n);
                FAIL () << "Expected " << input << " to throw an exception but it didn't.";
            } catch (...) {}
        }
    }

    void Interpreter::test_eval (std::string input, expression expect_eval) {
        auto [_, ev] = Machine.evaluate (read_line (input));
        auto ex = Machine.evaluate (expect_eval);
        EXPECT_EQ (ev, ex) << "expected " << input << " to evaluate to " << expect_eval;
    }

    void Interpreter::test_eval (std::string input, std::string expect_eval) {
        return test_eval (input, first (read_line (expect_eval)).Predicate);
    }

    void Interpreter::test_eval (std::string input, const char *expect_eval) {
        return test_eval (input, std::string {expect_eval});
    }

}

