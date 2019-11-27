#include "pch.h"
#include "syntax/token.h"
#include "test_api/util.h"

using namespace ionir::test;

TEST(TestApiTest, TrimSimpleString)
{
    EXPECT_EQ(util::trim(" test "), "test");
}

TEST(TestApiTest, TrimString)
{
    EXPECT_EQ(util::trim("  hello world  "), "hello world");
}

TEST(TestApiTest, LeftTrimString)
{
    EXPECT_EQ(util::leftTrim("  hello world  "), "hello world  ");
}

TEST(TestApiTest, RightTrimString)
{
    EXPECT_EQ(util::rightTrim("  hello world  "), "  hello world");
}
