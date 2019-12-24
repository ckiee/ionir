#include "syntax/token.h"
#include "test_api/bootstrap.h"
#include "pch.h"

using namespace ionir;

TEST(TokenTest, CorrectProperties) {
    Token token = Token(TokenType::Identifier, std::string("hello_world"), 123);

    EXPECT_EQ(token.getValue(), "hello_world");
    EXPECT_EQ(token.getType(), TokenType::Identifier);
    EXPECT_EQ(token.getStartPosition(), 123);

    // End position must be 123 + len("hello_world") (11) = 134.
    EXPECT_EQ(token.getEndPosition(), 134);
}

TEST(TokenTest, CreateDummy) {
    Token token = Token::createDummy(0);
    Token expected = Token(TokenType::Dummy, "", 0);

    EXPECT_EQ(expected, token);
}

TEST(TokenTest, DetermineWhetherIsDummy) {
    Token dummy = Token::createDummy(0);
    Token token = test::bootstrap::token();

    EXPECT_TRUE(dummy.isDummy());
    EXPECT_FALSE(token.isDummy());
}

TEST(TokenTest, EqualityAndDifference) {
    // Create test tokens.
    Token token1 = Token(TokenType::SymbolColon, ":", 5);
    Token token2 = Token(TokenType::SymbolColon, ":", 5);
    Token token3 = Token(TokenType::SymbolColon, "~", 5);

    // Expect equal.
    EXPECT_EQ(token1, token2);
    EXPECT_EQ(token2, token1);

    // Expect not to equal.
    EXPECT_NE(token1, token3);
    EXPECT_NE(token2, token3);
}
