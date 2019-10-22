#include "pch.h"
#include "syntax/token.h"

using namespace ::testing;

TEST(TokenTest, CorrectProperties)
{
    ionir::Token token = ionir::Token(ionir::TokenType::Identifier, std::string("hello_world"), 123);

    EXPECT_EQ(token.getValue(), "hello_world");
    EXPECT_EQ(token.getType(), ionir::TokenType::Identifier);
    EXPECT_EQ(token.getStartPosition(), 123);

    // End position must be 123 + len("hello_world") (11) = 134.
    EXPECT_EQ(token.getEndPosition(), 134);
}
