#pragma once

#include <string>
#include <ionir/misc/iterable.h>
#include "token_type.h"

namespace ionir {
    class Token {
    protected:
        TokenType type;

        std::string value;

        size_t startPosition;

        size_t lineNumber;

    public:
        static Token createDummy(size_t startPosition);

        Token(TokenType type, std::string value, size_t startPosition = 0, size_t lineNumber = 0);

        TokenType getType() const;

        std::string getValue() const;

        size_t getStartPosition() const;

        size_t getEndPosition() const;

        size_t getLineNumber() const;

        bool isDummy() const;

        bool operator==(const Token &other) const;

        bool operator!=(const Token &other) const;
    };

    std::ostream &operator<<(std::ostream &stream, Token &token);

    /**
     * An iterable list of tokens.
     */
    typedef Iterable<Token> TokenStream;
}
