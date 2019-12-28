#include <ionir/misc/util.h>
#include "pch.h"

using namespace ionir;

TEST(UtilEscapeRegex, IgnoreNonSpecialCharacters) {
    EXPECT_EQ(Util::escapeRegex("abc"), "abc");
    EXPECT_EQ(Util::escapeRegex("123"), "123");
}

TEST(UtilEscapeRegex, EscapeSpecialCharacters) {
    EXPECT_EQ(Util::escapeRegex("$^"), "\\$\\^");
}
