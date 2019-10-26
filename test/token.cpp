#include "pch.h"
#include "syntax/token.h"
#include "test_util.h"

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

TEST(TokenTest, CreateDummy)
{
    ionir::Token token = ionir::Token::createDummy(0);
    ionir::Token expected = ionir::Token(ionir::TokenType::Unknown, "", 0);

    EXPECT_EQ(expected, token);
}

TEST(TokenTest, DetermineWhetherIsDummy)
{
    ionir::Token dummy = ionir::Token::createDummy(0);
    ionir::Token token = ionir::testing::bootstrapToken(0);

    EXPECT_TRUE(dummy.isDummy());
    EXPECT_FALSE(token.isDummy());
}

TEST(TokenTest, EqualityAndDifference)
{
    // Create test tokens.
    ionir::Token token1 = ionir::Token(ionir::TokenType::SymbolColon, ":", 5);
    ionir::Token token2 = ionir::Token(ionir::TokenType::SymbolColon, ":", 5);
    ionir::Token token3 = ionir::Token(ionir::TokenType::SymbolColon, "~", 5);

    // Expect equal.
    EXPECT_EQ(token1, token2);
    EXPECT_EQ(token2, token1);

    // Expect not to equal.
    EXPECT_NE(token1, token3);
    EXPECT_NE(token2, token3);
}
