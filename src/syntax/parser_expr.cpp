#include <ionir/syntax/parser.h>

#include <utility>

namespace ionir {
    ionshared::OptPtr<Construct> Parser::parsePrimaryExpr(ionshared::Ptr<Construct> parent) {
        TokenKind tokenKind = this->stream.get().getKind();

        // Expression is a literal.
        if (Classifier::isLiteral(tokenKind)) {
            return this->parseValue();
        }

        // Otherwise, it must be a reference.
        return this->parseRef<>(std::move(parent));
    }
}
