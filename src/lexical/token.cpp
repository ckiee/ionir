#include <ionir/lexical/token.h>

namespace ionir {
    Token Token::createDummy(size_t startPosition) {
        return Token(TokenType::Dummy, "", startPosition);
    }

    Token::Token(TokenType type, std::string value, size_t startPosition)
        : type(type), value(value), startPosition(startPosition) {
        //
    }

    size_t Token::getStartPosition() const {
        return this->startPosition;
    }

    size_t Token::getEndPosition() const {
        return this->startPosition + this->value.length();
    }

    TokenType Token::getType() const {
        return this->type;
    }

    std::string Token::getValue() const {
        return this->value;
    }

    bool Token::isDummy() const {
        return this->type == TokenType::Dummy;
    }

    bool Token::operator==(const Token &other) const {
        return this->value == other.value &&
            this->type == other.type &&
            this->startPosition == other.startPosition;
    }

    bool Token::operator!=(const Token &other) const {
        return !(*this == other);
    }

    std::ostream &operator<<(std::ostream &stream, Token &token) {
        return stream << "Token(" << token.getValue() << ", " << token.getType() << ", " << token.getStartPosition()
            << "-" << token.getEndPosition() << ")";
    }
}
