#include <ionir/reporting/notice.h>

namespace ionir {
    std::string Notice::getText(NoticeType type) {
        // TODO: Hard-coded, use a map instead.
        switch (type) {
            case NoticeType::Warning: {
                return "Warning";
            }

            case NoticeType::Error: {
                return "Error";
            }

            case NoticeType::Fatal: {
                return "Fatal";
            }

            default: {
                return "Unknown";
            }
        }
    }

    Notice::Notice(NoticeContext context, NoticeType type, std::string message)
        : context(context), type(type), message(message) {
        //
    }

    NoticeContext Notice::getContext() const {
        return this->context;
    }

    NoticeType Notice::getType() const {
        return this->type;
    }

    std::string Notice::getMessage() const {
        return this->message;
    }

    std::string Notice::createTrace() const {
        return this->context.getFilePath() + ":" + std::to_string(this->context.getLineNumber()) + ":" +
            std::to_string(this->context.getPosition()) + " | " + Notice::getText(this->type) + ": " + this->message;
    }
}
