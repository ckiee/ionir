#pragma once

// TODO: Not being specific enough on name.
#define IONIR_DEFAULT_GRACE 2

#include <string>
#include <vector>
#include <ionir/lexical/token.h>
#include "notice.h"

namespace ionir {
    struct CodeBlockLine {
        std::string text;

        std::vector<Token> tokens;

        std::optional<uint32_t> lineNumber = std::nullopt;

        bool highlight = false;
    };

    typedef std::vector<CodeBlockLine> CodeBlock;

    class CodeBacktrack {
    private:
        std::string input;

        TokenStream stream;

    protected:
        static std::string resolveInputText(std::string input, std::vector<Token> lineBuffer);

    public:
        CodeBacktrack(std::string input, TokenStream stream);

        std::string getInput() const;

        TokenStream getTokenStream() const;

        std::optional<CodeBlock> createCodeBlockNear(uint32_t lineNumber, uint32_t grace = IONIR_DEFAULT_GRACE);

        std::optional<CodeBlock> createCodeBlockNear(Token token, uint32_t grace = IONIR_DEFAULT_GRACE);

        std::optional<CodeBlock> createCodeBlockNear(NoticeContext noticeContext, uint32_t grace = IONIR_DEFAULT_GRACE);

        std::optional<CodeBlock> createCodeBlockNear(Notice notice, uint32_t grace = IONIR_DEFAULT_GRACE);
    };
}
