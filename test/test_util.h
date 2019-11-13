#pragma once

#include <array>
#include <vector>
#include "syntax/token.h"
#include "misc/iterable.h"

namespace ionir::testing
{
Token bootstrapToken(int id)
{
    Token token = Token(TokenType::Unknown, std::string("test_" + std::to_string(id)), id);

    return token;
}

TokenStream bootstrapTokenStream(int amountOfItems = 1)
{
    std::vector<Token> tokens = {};

    // Populate the tokens vector.
    for (int i = 0; i < amountOfItems; i++)
    {
        tokens.push_back(bootstrapToken(i));
    }

    // Create the Stream and provide the tokens.
    TokenStream stream = TokenStream(tokens);

    return stream;
}

template <unsigned int N>
void compareTokenSets(std::array<Token, N> expected, std::vector<Token> actual)
{
    // Both sets should have the same length.
    EXPECT_EQ(expected.size(), actual.size());

    // Compare results by iterating over both expected and actual, resulting tokens.
    int i = 0;

    for (auto &token : actual)
    {
        // Compare iterator value with its corresponding expected token type.
        EXPECT_EQ(expected[i], token);

        // Increment counter to prepare for next iteration.
        i++;
    }
}
} // namespace ionir::testing
