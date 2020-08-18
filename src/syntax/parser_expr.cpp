#include <ionir/syntax/parser.h>

#include <utility>

namespace ionir {
    AstPtrResult<> Parser::parsePrimaryExpr(const ionshared::Ptr<Construct> &parent) {
        TokenKind tokenKind = this->stream.get().getKind();

        // Expression is a literal.
        if (Classifier::isLiteral(tokenKind)) {
            return this->parseValue();
        }

        // Otherwise, it must be a reference.
        return this->parseRef<>(std::move(parent));
    }
}
