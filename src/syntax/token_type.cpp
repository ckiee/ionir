#include <iostream>
#include "token_type.hpp"

namespace ionir
{
void testt()
{
}
std::ostream &operator<<(std::ostream &stream, const ionir::TokenType &tokenType)
{
    return stream << "TokenType(" << (int)tokenType << ")";
}
} // namespace ionir
