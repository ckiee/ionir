#include <sstream>
#include <ionir/misc/util.h>
#include <ionir/reporting/code_backtrack.h>
#include <ionir/reporting/code_trace_block.h>

namespace ionir {
    CodeBacktrack::CodeBacktrack(TokenStream &stream) : stream(stream) {
        //
    }

    std::optional<std::string> CodeBacktrack::createCodeBlockNear(uint32_t lineNumber, uint32_t grace) {
        // TODO: Cannot compare stream size with line number.
        size_t streamSize = this->stream.getSize();

        std::stringstream codeBlock;

        // Separate code block from previous messages by a single line.
        codeBlock << std::endl << std::endl;

        if (streamSize - 1 < lineNumber) {
            return std::nullopt;
        }

        // Compute start & end line for the code block.
        uint32_t start = grace > lineNumber ? 0 : lineNumber - grace;

        // TODO: Will never show extra ones after index (grace). Address issue.
        uint32_t end = (streamSize >= lineNumber + grace) ? lineNumber + grace : lineNumber;

        this->stream.begin();

        uint32_t lineCounter = 0;
        std::optional<Token> tokenBuffer = std::nullopt;
        std::vector<std::string> lineBuffer = {};

        while (lineCounter != start) {
            tokenBuffer = this->stream.next();

            if (tokenBuffer->getLineNumber() != lineCounter) {
                lineCounter++;
            }
        }

        // TODO: Not skipping one iteration? Shouldn't be using .get() on 2nd loop?

        while (lineCounter != end) {
            tokenBuffer = this->stream.next();

            if (tokenBuffer->getLineNumber() != lineCounter) {
                std::cout << "Line: " << Util::joinStringVector(lineBuffer) << std::endl;
                codeBlock << CodeTraceBlock::createLine(Util::joinStringVector(lineBuffer), lineCounter + 1);
                lineBuffer.clear();
                lineCounter++;
            }
            else {
                lineBuffer.push_back(tokenBuffer->getValue());
            }
        }

        return codeBlock.str();
    }

    std::optional<std::string> CodeBacktrack::createCodeBlockNear(Token token, uint32_t grace) {
        std::optional<uint32_t> location = this->stream.locate(token);

        if (!location.has_value()) {
            return std::nullopt;
        }

        return this->createCodeBlockNear(*location, grace);
    }
}
