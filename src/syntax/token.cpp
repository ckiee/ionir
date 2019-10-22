#pragma once

#include <iostream>
#include "token.hpp"

namespace ionir
{
class Token
{
    std::ostream &operator<<(std::ostream &stream, Token &token)
    {
        return stream << "Token(" << token.getValue() << ", " << token.getType() << ")";
    }
} // namespace ionir
