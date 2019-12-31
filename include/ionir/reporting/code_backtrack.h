#pragma once

#include <string>
#include <ionir/lexical/token.h>

namespace ionir {
    class CodeBacktrack {
    private:
        TokenStream &stream;

    public:
        explicit CodeBacktrack(TokenStream &stream);

        std::optional<std::string> createCodeBlockNear(uint32_t index, uint32_t grace = 3);

        std::optional<std::string> createCodeBlockNear(Token token, uint32_t grace = 3);
    };
}
