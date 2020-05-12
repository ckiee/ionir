#pragma once

#include <string>
#include <ionir/misc/iterable.h>
#include "token_kind.h"

namespace ionir {
    class Token {
    private:
        TokenKind kind;

        std::string value;

        uint32_t startPosition;

        uint32_t lineNumber;

    public:
        static Token createDummy(uint32_t startPosition) noexcept;

        Token(TokenKind kind, std::string value, uint32_t startPosition = 0, uint32_t lineNumber = 0);

        TokenKind getKind() const noexcept;

        std::string getValue() const noexcept;

        uint32_t getStartPosition() const noexcept;

        uint32_t getEndPosition() const noexcept;

        uint32_t getLineNumber() const noexcept;

        bool isDummy() const noexcept;

        std::string getName() const;

        bool operator==(const Token &other) const;

        bool operator!=(const Token &other) const;
    };

    std::ostream &operator<<(std::ostream &stream, Token &token);

    /**
     * An iterable list of tokens.
     */
    typedef Iterable<Token> TokenStream;
}
