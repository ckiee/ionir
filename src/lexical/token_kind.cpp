#include <ionir/lexical/token_kind.h>

namespace ionir {
    std::ostream &operator<<(std::ostream &stream, const ionir::TokenKind &tokenKind) {
        return stream << "TokenKind(" << (int)tokenKind << ")";
    }
}
