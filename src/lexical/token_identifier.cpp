#include <algorithm>
#include <ionir/lexical/token_identifier.h>

namespace ionir {
    bool TokenIdentifier::contains(std::vector<TokenType> subject, TokenType item) {
        return std::find(subject.begin(), subject.end(), item) != subject.end();
    }

    bool TokenIdentifier::isSymbol(TokenType type) {
        return TokenIdentifier::contains(TokenConst::getSymbols(), type);
    }

    bool TokenIdentifier::isNumeric(TokenType type) {
        // TODO: Need to define numeric group.
        return false;
    }

    bool TokenIdentifier::isOperator(TokenType type) {
        return TokenIdentifier::contains(TokenConst::getOperators(), type);
    }

    bool TokenIdentifier::isType(TokenType type) {
        return TokenIdentifier::contains(TokenConst::getTypes(), type);
    }
}
