#include <ionir/lexical/classifier.h>

namespace ionir {
    bool Classifier::isSymbol(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getSymbols(), tokenKind);
    }

    bool Classifier::isNumeric(TokenKind tokenKind) {
        // TODO: Need to define numeric group.
        return false;
    }

    bool Classifier::isOperator(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getOperators(), tokenKind);
    }

    bool Classifier::isType(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getTypes(), tokenKind);
    }

    bool Classifier::isKeyword(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getKeywords(), tokenKind);
    }

    bool Classifier::isInst(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getInsts(), tokenKind);
    }

    bool Classifier::isUnsignedType(TokenKind tokenKind) {
        return tokenKind == TokenKind::TypeUnsignedInt16
            || tokenKind == TokenKind::TypeUnsignedInt32
            || tokenKind == TokenKind::TypeUnsignedInt64;
    }
}
