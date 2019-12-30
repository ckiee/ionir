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
    private:
        NoticeContext context;

        NoticeType type;

        std::string message;

    public:
        static std::string getText(NoticeType type);

        Notice(NoticeContext context, NoticeType type, std::string message);

        NoticeContext getContext() const;

        NoticeType getType() const;

        std::string getMessage() const;

        std::string createTrace() const;
    };
}
