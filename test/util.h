#pragma once

#include "syntax/stream.hpp"

namespace ionir::testing
{
ionir::Token bootstrapToken(int id)
{
    ionir::Token token = ionir::Token(ionir::TokenType::Unknown, std::string("test_" + std::to_string(id)), id);

    return token;
}

ionir::TokenStream bootstrapTokenStream(int amountOfItems = 1)
{
    std::vector<ionir::Token> tokens = {};

    // Populate the tokens vector.
    for (int i = 0; i < amountOfItems; i++)
    {
        tokens.push_back(bootstrapToken(i));
    }

    // Create the Stream and provide the tokens.
    ionir::TokenStream stream = ionir::TokenStream(tokens);

    return stream;
}
} // namespace ionir::testing
