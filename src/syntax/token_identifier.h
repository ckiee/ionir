#pragma once

#include "misc/token_constants.h"

namespace ionir
{
class TokenIdentifier
{
protected:
    TokenConstants *constants;

    bool contains(std::vector<TokenType> subject, TokenType item);

public:
    TokenIdentifier(TokenConstants *constants);

    bool isSymbol(TokenType type);

    bool isNumeric(TokenType type);

    bool isOperator(TokenType type);
};
} // namespace ionir
