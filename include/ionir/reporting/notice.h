#pragma once

#include <string>
#include "notice_context.h"

namespace ionir {
    enum class NoticeType {
        Warning,

        Error,

        Fatal
    };

    class Notice {
    protected:
        NoticeContext context;

        NoticeType type;

        std::string message;

    public:
        Notice(NoticeContext context, NoticeType type, std::string message);

        NoticeContext getContext() const;

        NoticeType getType() const;

        std::string getMessage() const;

        std::string createTrace() const;
    };
}
