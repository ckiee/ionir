#include <ionir/lexical/token.h>

namespace ionir {
    Token Token::createDummy(uint32_t startPosition) {
        return Token(TokenType::Dummy, "", startPosition);
    }

    Token::Token(TokenType type, std::string value, uint32_t startPosition, uint32_t lineNumber)
        : type(type), value(value), startPosition(startPosition), lineNumber(lineNumber) {
        //
    }

    TokenType Token::getType() const {
        return this->type;
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
        // TODO: Include line number as well.
        return stream << "Token(" << token.getValue() << ", " << token.getType() << ", " << token.getStartPosition()
            << "-" << token.getEndPosition() << ")";
    }
}
