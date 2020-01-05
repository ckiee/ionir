#pragma once

#include <string>
#include <ionir/misc/iterable.h>
#include "token_kind.h"

namespace ionir {
    class Token {
    protected:
        TokenKind kind;

        std::string value;

        uint32_t startPosition;

        uint32_t lineNumber;

    public:
        static Token createDummy(const uint32_t startPosition);

        Token(const TokenKind kind, const std::string value, const uint32_t startPosition = 0,
            const uint32_t lineNumber = 0);

        TokenKind getKind() const;

        std::string getValue() const;

        uint32_t getStartPosition() const;

        uint32_t getEndPosition() const;

        uint32_t getLineNumber() const;

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
