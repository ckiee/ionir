#include <algorithm>
#include <ionir/lexical/token_identifier.h>

namespace ionir {
    bool TokenIdentifier::contains(std::vector<TokenKind> subject, TokenKind item) {
        return std::find(subject.begin(), subject.end(), item) != subject.end();
    }

    bool TokenIdentifier::isSymbol(TokenKind tokenKind) {
        return TokenIdentifier::contains(TokenConst::getSymbols(), tokenKind);
    }

    bool TokenIdentifier::isNumeric(TokenKind tokenKind) {
        // TODO: Need to define numeric group.
        return false;
    }

    bool TokenIdentifier::isOperator(TokenKind tokenKind) {
        return TokenIdentifier::contains(TokenConst::getOperators(), tokenKind);
    }

    bool TokenIdentifier::isType(TokenKind tokenKind) {
        return TokenIdentifier::contains(TokenConst::getTypes(), tokenKind);
    }

    bool TokenIdentifier::isKeyword(TokenKind tokenKind) {
        return TokenIdentifier::contains(TokenConst::getKeywords(), tokenKind);
    }

    bool TokenIdentifier::isInst(TokenKind tokenKind) {
        return TokenIdentifier::contains(TokenConst::getInsts(), tokenKind);
    }
}
