#include <sstream>
#include <ionir/misc/util.h>
#include <ionir/reporting/code_backtrack.h>

namespace ionir {
    CodeBacktrack::CodeBacktrack(TokenStream &stream) : stream(stream) {
        //
    }

    std::optional<CodeBlock> CodeBacktrack::createCodeBlockNear(uint32_t lineNumber, uint32_t grace) {
        CodeBlock codeBlock;

        // Compute start & end line for the code block.
        uint32_t start = grace >= lineNumber ? 0 : lineNumber - grace;
        uint32_t end = lineNumber + grace;

        this->stream.begin();

        uint32_t lineCounter = 0;
        std::optional<Token> tokenBuffer = std::nullopt;
        std::vector<Token> lineBuffer = {};
        bool prime = true;
        bool met = false;

        while (lineCounter != start) {
            if (!this->stream.hasNext()) {
                // Could not reach starting point.
                return std::nullopt;
            }

            tokenBuffer = this->stream.next();

            if (tokenBuffer->getLineNumber() != lineCounter) {
                lineCounter = tokenBuffer->getLineNumber();
            }
        }

        while (lineCounter != end) {
            met = lineCounter >= lineNumber;

            if (!prime) {
                tokenBuffer = this->stream.next();
            }
            else {
                tokenBuffer = this->stream.get();
                prime = false;
            }

            bool streamHasNext = this->stream.hasNext();

            lineBuffer.push_back(*tokenBuffer);

            if (stream.peek()->getLineNumber() != lineCounter) {
                // TODO: Extract text using Iterable::slice(from, to).
                std::string text = "todo";

                codeBlock.push_back(CodeBlockLine{
                    text,
                    lineBuffer,
                    lineNumber
                });

                lineBuffer.clear();
                lineCounter = stream.peek()->getLineNumber();

                continue;
            }

            // Could not reach end point.
            if (!streamHasNext && !met) {
                return std::nullopt;
            }
                // Return requirements have been met. Do not continue.
            else if (!streamHasNext) {
                // TODO: Extract text using Iterable::slice(from, to).
                std::string text = "todo";

                codeBlock.push_back(CodeBlockLine{
                    text,
                    lineBuffer,
                    lineNumber
                });

                return codeBlock;
            }
        }

        return codeBlock;
    }

    std::optional<CodeBlock> CodeBacktrack::createCodeBlockNear(Token token, uint32_t grace) {
        return this->createCodeBlockNear(token.getLineNumber(), grace);
    }

    std::optional<CodeBlock> CodeBacktrack::createCodeBlockNear(NoticeContext noticeContext, uint32_t grace) {
        return this->createCodeBlockNear(noticeContext.lineNumber);
    }

    std::optional<CodeBlock> CodeBacktrack::createCodeBlockNear(Notice notice, uint32_t grace) {
        return this->createCodeBlockNear(notice.getContext());
    }
}
