#pragma once

#include "notice_context.h"
#include "notice.h"

namespace ionir {
    class NoticeFactory {
    private:
        NoticeContext context;

    public:
        explicit NoticeFactory(NoticeContext context);

        NoticeContext &getContext();

        void setContext(NoticeContext &context);

        Notice make(NoticeType type, std::string message);
    };
}
