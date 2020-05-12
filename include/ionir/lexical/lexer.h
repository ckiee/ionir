#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <utility>
#include <ionir/const/token_const.h>
#include <ionir/misc/util.h>
#include <ionir/misc/regex.h>
#include <ionir/misc/iterable.h>
#include "token.h"

namespace ionir {
    struct MatchResult {
        bool success;

        std::optional<std::string> matchedValue = std::nullopt;

        std::optional<std::string> capturedValue = std::nullopt;
    };

    struct MatchOpts {
        Token &token;

        TokenKind tokenKind;

        std::regex regex;

        bool expectCapturedValue = false;
    };

    class Lexer : public Generator<Token> {
    private:
        std::string input;

        size_t length;

        size_t index;

        SimplePairVector simpleIds;

        std::vector<std::pair<std::regex, TokenKind>> complexIds;

    protected:
        char getChar() const noexcept;

        std::string getCharAsString() const noexcept;

        size_t getLength() const noexcept;

        size_t setIndex(size_t index) noexcept;

        size_t skip(size_t amount = 1);

        MatchResult matchExpression(MatchOpts opts);

        void processWhitespace();

    public:
        Lexer(std::string input);

        size_t getIndex() const noexcept;

        virtual void begin();

        /**
         * Whether the index has not reached the input's length.
         */
        virtual bool hasNext() const;

        /**
         * Process the next token.
         */
        virtual std::optional<Token> tryNext();

        std::string getInput() const noexcept;

        std::vector<Token> scan();
    };
}
