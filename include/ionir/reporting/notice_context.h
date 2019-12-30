#pragma once

#include <string>

namespace ionir {
    class NoticeContext {
    protected:
        std::string filePath;

        size_t lineNumber;

        size_t position;

    public:
        NoticeContext(std::string filePath, size_t lineNumber, size_t position);

        std::string getFilePath() const;

        size_t getLineNumber() const;

        size_t getPosition() const;
    };
}
