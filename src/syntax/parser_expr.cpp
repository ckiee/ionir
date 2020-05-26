#include <ionir/syntax/parser.h>

namespace ionir {
    OptPtr<Construct> Parser::parsePrimaryExpr(Ptr<Construct> parent) {
        TokenKind tokenKind = this->stream.get().getKind();

        // Expression is a literal.
        if (Classifier::isLiteral(tokenKind)) {
            return this->parseValue();
        }

        // Otherwise, it must be a reference.
        return this->parseRef<>(parent);
    }
}
