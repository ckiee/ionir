#pragma once

#include <string>
#include <vector>

namespace ionir {
    enum class NoticeType {
        Warning,

        Error,

        Fatal
    };

    struct NoticeContext {
        std::string filePath;

        uint32_t lineNumber;

        uint32_t position;
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

    typedef std::vector<Notice> StackTrace;
}
