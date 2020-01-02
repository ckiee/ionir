#pragma once

#include <ionir/misc/helpers.h>
#include <ionir/const/token_const.h>

namespace ionir {
    class TokenIdentifier {
    protected:
        static bool contains(TokenTypeVector subject, TokenType item);

    public:
        static bool isSymbol(TokenType type);

        static bool isNumeric(TokenType type);

        static bool isOperator(TokenType type);

        static bool isType(TokenType type);

        static bool isKeyword(TokenType type);
    };
}
