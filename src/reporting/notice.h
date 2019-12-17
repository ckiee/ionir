#pragma once

#include <string>
#include "notice_type.h"
#include "notice_context.h"

namespace ionir
{
class Notice
{
protected:
    NoticeContext context;

    NoticeType type;

    std::string message;

public:
    Notice(NoticeContext context, NoticeType type, std::string message);

    NoticeContext getContext() const;

    NoticeType getType() const;

    std::string getMessage() const;
};
} // namespace ionir
