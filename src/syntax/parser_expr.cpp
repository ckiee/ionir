#include <ionir/syntax/parser.h>

namespace ionir {
    AstPtrResult<> Parser::parsePrimaryExpr(const ionshared::Ptr<Construct> &parent) {
        TokenKind tokenKind = this->stream.get().getKind();

        // Expression is a literal.
        if (Classifier::isLiteral(tokenKind)) {
            return Util::castAstPtrResult<Value<>>(this->parseValue());
        }

        // Otherwise, it must be a reference.
        return Util::castAstPtrResult<Ref<>>(this->parseRef<>(parent));
    }
}
