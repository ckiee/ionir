#include "pch.h"
#include "syntax/token.h"
#include "test_api/util.h"

using namespace ionir::test;

TEST(TestApiTest, TrimSimpleString)
{
    EXPECT_EQ(util::trimString(" test "), "test");
}

TEST(TestApiTest, TrimString)
{
    EXPECT_EQ(util::trimString("  hello world  "), "hello world");
}
