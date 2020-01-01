#pragma once

#include <optional>
#include <vector>
#include <ionir/lexical/token.h>

namespace ionir {
    struct CodeBlockLine {
        std::string text;

        std::vector<Token> tokens;

        std::optional<uint32_t> lineNumber = std::nullopt;

        bool highlight = false;
    };

    class CodeTraceBlock {
    private:
        std::vector<CodeBlockLine> lines;

    public:
        static const std::string continued;

        static std::string createGutter(std::optional<uint32_t> lineNumber);

        static std::string createLine(std::string text, std::optional<uint32_t> lineNumber);

        explicit CodeTraceBlock();

        std::vector<CodeBlockLine> &getLines();

        void setLines(std::vector<CodeBlockLine> lines);
    };
}
