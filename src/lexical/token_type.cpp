#include <ionir/lexical/token_type.h>

namespace ionir {
    std::ostream &operator<<(std::ostream &stream, const ionir::TokenKind &tokenKind) {
        return stream << "TokenKind(" << (int)tokenKind << ")";
    }
}
