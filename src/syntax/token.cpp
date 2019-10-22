#pragma once

#include <iostream>
#include "token.h"

namespace ionir
{
std::ostream &operator<<(std::ostream &stream, Token &token)
{
    return stream << "Token(" << token.getValue() << ", " << token.getType() << ")";
}
} // namespace ionir
