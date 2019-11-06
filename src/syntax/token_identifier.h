#pragma once

#include "syntax/token_type.h"

namespace ionir
{
class TokenIdentifier
{
public:
    bool isSymbol(TokenType type);
};
} // namespace ionir
