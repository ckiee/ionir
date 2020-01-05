#include <ionir/lexical/token.h>

namespace ionir {
    Token Token::createDummy(const uint32_t startPosition) {
        return Token(TokenKind::Dummy, "", startPosition);
    }

    Token::Token(const TokenKind kind, const std::string value, const uint32_t startPosition, const uint32_t lineNumber)
        : kind(kind), value(value), startPosition(startPosition), lineNumber(lineNumber) {
        //
    }

    TokenKind Token::getKind() const {
        return this->kind;
    }

    std::string Token::getValue() const {
        return this->value;
    }

    uint32_t Token::getStartPosition() const {
        return this->startPosition;
    }

    uint32_t Token::getEndPosition() const {
        return this->startPosition + this->value.length();
    }

    uint32_t Token::getLineNumber() const {
        return this->lineNumber;
    }

    bool Token::isDummy() const {
        return this->kind == TokenKind::Dummy;
    }

    bool Token::operator==(const Token &other) const {
        return this->value == other.value &&
            this->kind == other.kind &&
            this->startPosition == other.startPosition;
    }

    bool Token::operator!=(const Token &other) const {
        return !(*this == other);
    }

    std::ostream &operator<<(std::ostream &stream, Token &token) {
        // TODO: Include line number as well.
        return stream << "Token(" << token.getValue() << ", " << token.getKind() << ", " << token.getStartPosition()
            << "-" << token.getEndPosition() << ")";
    }
}
