#include <ionir/lexical/token_identifier.h>

namespace ionir {
    bool TokenIdentifier::isSymbol(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getSymbols(), tokenKind);
    }

    bool TokenIdentifier::isNumeric(TokenKind tokenKind) {
        // TODO: Need to define numeric group.
        return false;
    }

    bool TokenIdentifier::isOperator(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getOperators(), tokenKind);
    }

    bool TokenIdentifier::isType(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getTypes(), tokenKind);
    }

    bool TokenIdentifier::isKeyword(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getKeywords(), tokenKind);
    }

    bool TokenIdentifier::isInst(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getInsts(), tokenKind);
    }
}
