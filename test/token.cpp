#pragma once

#include "pch.h"
#include "syntax/token.h"

using namespace ::testing;

TEST(TokenTest, CorrectProperties)
{
    ionir::Token token = ionir::Token(ionir::TokenType::Identifier, std::string("hello_world"), 123);

    EXPECT_EQ(token.getValue(), "hello_world");
    EXPECT_EQ(token.getType(), ionir::TokenType::Identifier);
    EXPECT_EQ(token.getStartPosition(), 123);
}
