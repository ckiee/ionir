#include <ionir/reporting/code_trace_block.h>

namespace ionir {
    const std::string CodeTraceBlock::continued = "...";

    std::string CodeTraceBlock::createGutter(std::optional<uint32_t> lineNumber) {
        return (lineNumber.has_value() ? std::to_string(*lineNumber) : " ") + " | ";
    }

    std::string CodeTraceBlock::createLine(std::string text, std::optional<uint32_t> lineNumber) {
        return "\t" + CodeTraceBlock::createGutter(lineNumber) + text + "\n";
    }

    CodeTraceBlock::CodeTraceBlock() : lines({}) {
        //
    }

    std::vector<CodeBlockLine> &CodeTraceBlock::getLines() {
        return this->lines;
    }

    void CodeTraceBlock::setLines(std::vector<CodeBlockLine> lines) {
        this->lines = lines;
    }
}
