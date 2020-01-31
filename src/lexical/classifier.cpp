#include <ionir/lexical/classifier.h>
#include <ionir/misc/util.h>

namespace ionir {
    bool Classifier::isSymbol(TokenKind tokenKind) {

        return Util::mapContains<std::string, TokenKind>(TokenConst::getSymbols(), tokenKind);
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

    bool Classifier::isUnsignedIntegerType(TokenKind tokenKind) {
        return tokenKind == TokenKind::TypeUnsignedInt16
            || tokenKind == TokenKind::TypeUnsignedInt32
            || tokenKind == TokenKind::TypeUnsignedInt64;
    }

    bool Classifier::isIntegerType(TokenKind tokenKind) {
        return tokenKind == TokenKind::TypeInt16
            || tokenKind == TokenKind::TypeInt32
            || tokenKind == TokenKind::TypeInt64
            || Classifier::isUnsignedIntegerType(tokenKind);
    }

    bool Classifier::isKeyword(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getKeywords(), tokenKind);
    }

    bool Classifier::isInst(TokenKind tokenKind) {
        return TokenConst::contains(TokenConst::getInsts(), tokenKind);
    }
}
