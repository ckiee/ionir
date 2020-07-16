#include <ionir/lexical/token.h>
#include <ionir/const/token_const.h>

namespace ionir {
    Token Token::createDummy(uint32_t startPosition) noexcept {
        return Token(TokenKind::Dummy, "", startPosition);
    }

    Token::Token(TokenKind kind, std::string value, uint32_t startPosition, uint32_t lineNumber)
        : BareToken(kind, value, startPosition, lineNumber) {
        //
    }

    bool Token::isDummy() const noexcept {
        return this->getKind() == TokenKind::Dummy;
    }

    std::string Token::getName() const {
        std::optional<std::string> name = TokenConst::getTokenKindName(this->getKind());

        return name.value_or("Unnamed");
    }

    std::ostream &operator<<(std::ostream &stream, Token &token) {
        // TODO: Include line number as well.
        return stream << "Token(" << token.getValue() << ", " << token.getKind() << ", " << token.getStartPosition()
            << "-" << token.getEndPosition() << ")";
    }
}
