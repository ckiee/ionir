#pragma once

// TODO: Not being specific enough on name.
#define IONIR_DEFAULT_GRACE 2

#include <string>
#include <ionir/lexical/token.h>

namespace ionir {
    class CodeBacktrack {
    private:
        TokenStream &stream;

    public:
        explicit CodeBacktrack(TokenStream &stream);

        std::optional<std::string> createCodeBlockNear(uint32_t lineNumber, uint32_t grace = IONIR_DEFAULT_GRACE);

        std::optional<std::string> createCodeBlockNear(Token token, uint32_t grace = IONIR_DEFAULT_GRACE);
    };
}
