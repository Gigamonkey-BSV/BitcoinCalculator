#include <Diophant/parse/parser.hpp>
#include <Diophant/values/leaf.hpp>
#include <Diophant/values/lambda.hpp>
#include <Diophant/replace.hpp>
#include "gtest/gtest.h"

namespace Diophant {
    class Match : public ::testing::Test {
    protected:
        static machine Machine;

        // Runs once before *any* test in this suite runs.
        static void SetUpTestSuite () {}

        // Runs once after *all* tests in this suite finish.
        static void TearDownTestSuite () {}

        void expect_match (std::string left, std::string right) {
            auto mzzz = match (Machine, read_pattern (left), read_pattern (right));
            std::cout << " matching " << left << " against " << right << "; got " << mzzz << std::endl;
            EXPECT_TRUE (bool (mzzz)) << "expect " << left << " to match " << right;
        }

        void expect_not_match (std::string left, std::string right) {
            EXPECT_FALSE (bool (match (Machine, read_pattern (left), read_pattern (right)))) << "expect " << left << " not to match " << right;
        }
    };

    machine Match::Machine = initialize ();

    TEST_F (Match, Match) {

        // for non patterns, matching is equality.
        expect_match ("1", "1");
        expect_not_match ("1", " 2");

        // blank matches anything.
        expect_match ("_", "_");
        expect_match ("_", "1");
        expect_match ("_", "2");
        expect_not_match ("1", "_");

        expect_match ("_x", "_");
        expect_match ("_x", "_y");
        expect_match ("_x", "1");
        expect_match ("_y", "1");
        expect_match ("_x", "2");
        expect_not_match ("1", "_x");
/*
        // match against types.
        expect_match ("_", "_n:N");
        expect_not_match ("_n:N", "_");

        expect_match ("_:N", "_:N");
        expect_match ("_:N", "1");
        expect_match ("_:N", "2");

        expect_not_match ("1", "_:N");
        expect_not_match ("_:string", "_:N");

        // not the right type.
        expect_not_match ("_x:string", "1");
        expect_match ("_n:N", "1");
        expect_match ("_n:N", "_m:N");
        expect_not_match ("1", "_n:N");

        // match against arity
        expect_match ("_ _", "_ _");
        expect_not_match ("f _ _", "f _");
        expect_not_match ("f _", "f _ _");
        expect_not_match ("f _", "g _");
        expect_match ("f _", "f x");

        // patterns with repeated symbols.
        expect_match ("f _x _x", "f 2 2");
        expect_not_match ("f _x _x", "f 2 3");
        expect_not_match ("f _x _x", "f _ _");
        expect_not_match ("f _ _", "f _x _x");
        expect_not_match ("f _x _y", "f _x _x");
        expect_not_match ("f 2 2", "f _x _x");

        // nested patterns.
        expect_not_match ("f _x _y:string", "f _x:Z _y");
        expect_not_match ("f _x:Z _y", "f _x _y:string");
        expect_not_match ("f _x _x _y", "f _x _y _y");
        expect_not_match ("f _x _y _y", "f _x _x _y");*/
    }
}
