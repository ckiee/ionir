#pragma once

#include <ionir/misc/helpers.h>
#include <ionir/const/token_const.h>

namespace ionir {
    class TokenIdentifier {
    public:
        static bool isSymbol(TokenKind tokenKind);

        static bool isNumeric(TokenKind tokenKind);

        static bool isOperator(TokenKind tokenKind);

        static bool isType(TokenKind tokenKind);

        static bool isKeyword(TokenKind tokenKind);

        static bool isInst(TokenKind tokenKind);
    };
}
