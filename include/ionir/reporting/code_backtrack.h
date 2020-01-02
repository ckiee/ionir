#pragma once

// TODO: Not being specific enough on name.
#define IONIR_DEFAULT_GRACE 2

#include <string>
#include <vector>
#include <ionir/lexical/token.h>

namespace ionir {
    struct CodeBlockLine {
        std::string text;

        std::vector<ionir::Token> tokens;

        std::optional<uint32_t> lineNumber = std::nullopt;

        bool highlight = false;
    };

    class CodeBacktrack {
    private:
        TokenStream &stream;

    public:
        explicit CodeBacktrack(TokenStream &stream);

        std::optional<std::vector<CodeBlockLine>>
        createCodeBlockNear(uint32_t lineNumber, uint32_t grace = IONIR_DEFAULT_GRACE);

        std::optional<std::vector<CodeBlockLine>>
        createCodeBlockNear(Token token, uint32_t grace = IONIR_DEFAULT_GRACE);
    };
}
