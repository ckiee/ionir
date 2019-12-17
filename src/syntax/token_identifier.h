#pragma once

#include "misc/helpers.h"
#include "constants/token_const.h"

namespace ionir
{
class TokenIdentifier
{
protected:
    static bool contains(TokenTypeVector subject, TokenType item);

public:
    static bool isSymbol(TokenType type);

    static bool isNumeric(TokenType type);

    static bool isOperator(TokenType type);
};
} // namespace ionir
