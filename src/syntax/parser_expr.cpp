#include <ionir/syntax/parser.h>

namespace ionir {
    AstPtrResult<> Parser::parsePrimaryExpr(const ionshared::Ptr<Construct> &parent) {
        TokenKind tokenKind = this->tokenStream.get().getKind();

        // Expression is a literal.
        if (Classifier::isLiteral(tokenKind)) {
            return util::castAstPtrResult<Value<>>(this->parseValue());
        }

        // Otherwise, it must be a reference.
        return util::castAstPtrResult<Ref<>>(this->parseRef<>(parent));
    }
}
