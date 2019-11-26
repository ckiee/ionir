#include "pch.h"
#include "misc/util.h"

TEST(UtilEscapeRegex, IgnoreNonSpecialCharacters)
{
    EXPECT_EQ(ionir::Util::escapeRegex("abc"), "abc");
    EXPECT_EQ(ionir::Util::escapeRegex("123"), "123");
}

TEST(UtilEscapeRegex, EscapeSpecialCharacters)
{
    EXPECT_EQ(ionir::Util::escapeRegex("$^"), "\\$\\^");
}
