#include <ionir/reporting/notice_context.h>

namespace ionir {
    NoticeContext::NoticeContext(std::string filePath, size_t lineNumber, size_t position) : filePath(filePath),
        lineNumber(lineNumber), position(position) {
        //
    }

    std::string NoticeContext::getFilePath() const {
        return this->filePath;
    }

    size_t NoticeContext::getLineNumber() const {
        return this->lineNumber;
    }

    size_t NoticeContext::getPosition() const {
        return this->position;
    }
}
