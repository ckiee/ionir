#include "notice.h"

namespace ionir
{
Notice::Notice(NoticeContext context, NoticeType type, std::string message) : context(context), type(type), message(message)
{
    //
}

NoticeContext Notice::getContext() const
{
    return this->context;
}

NoticeType Notice::getType() const
{
    return this->type;
}

std::string Notice::getMessage() const
{
    return this->message;
}
} // namespace ionir
