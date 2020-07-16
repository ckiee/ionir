#pragma once

#include <ionshared/lexical/bare_token.h>
#include <ionshared/misc/iterable.h>
#include "token_kind.h"

namespace ionir {
    class Token : public ionshared::BareToken<TokenKind> {
    public:
        static Token createDummy(uint32_t startPosition) noexcept;

        Token(TokenKind kind, std::string value, uint32_t startPosition = 0, uint32_t lineNumber = 0);

        bool isDummy() const noexcept;

        std::string getName() const;
    };

    std::ostream &operator<<(std::ostream &stream, Token &token);

    /**
     * An iterable list of IonIR tokens.
     */
    typedef ionshared::Iterable<Token> TokenStream;
}
