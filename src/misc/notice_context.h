#pragma once

#include <string>

namespace ionir
{
class NoticeContext
{
protected:
    std::string fileName;

    int lineNumber;

    int position;

public:
    NoticeContext(std::string fileName, int lineNumber, int position);

    std::string getFileName() const;

    int getLineNumber() const;

    int getPosition() const;
};
} // namespace ionir
