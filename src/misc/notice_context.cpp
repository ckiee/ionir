#include "notice_context.h"

namespace ionir
{
NoticeContext::NoticeContext(std::string fileName, int lineNumber, int position) : fileName(fileName), lineNumber(lineNumber), position(position)
{
    //
}

std::string NoticeContext::getFileName() const
{
    return this->fileName;
}

int NoticeContext::getLineNumber() const
{
    return this->lineNumber;
}

int NoticeContext::getPosition() const
{
    return this->position;
}
} // namespace ionir
