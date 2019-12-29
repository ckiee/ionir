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

    class Lexer : public Generator<Token> {
    private:
        std::string input;

        size_t length;

        size_t index;

        SimplePairVector simpleIds;

        std::vector<std::pair<std::regex, TokenType>> complexIds;

    protected:
        char getChar() const;

        std::string getCharAsString() const;

        size_t getLength() const;

        size_t setIndex(size_t index);

        size_t skip(size_t amount = 1);

        MatchResult matchExpression(Token &token, TokenType type, std::regex regex, bool expectCapturedValue = false);

        void processWhitespace();

    public:
        size_t getIndex() const;

        virtual void begin();

        /**
         * Whether the index has not reached the input's length.
         */
        virtual bool hasNext() const;

        /**
         * Process the next token.
         */
        virtual std::optional<Token> tryNext();

        Lexer(std::string input);

        std::string getInput() const;

        std::vector<Token> scan();
    };
}
