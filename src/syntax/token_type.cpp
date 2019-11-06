#include "token_type.h"

namespace ionir
{
inline std::ostream &operator<<(std::ostream &stream, const ionir::TokenType &tokenType)
{
    return stream << "TokenType(" << (int)tokenType << ")";
}
} // namespace ionir
