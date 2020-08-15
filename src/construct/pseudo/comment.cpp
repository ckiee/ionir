#include <ionir/construct/pseudo/comment.h>

namespace ionir {
    Comment::Comment(bool isMultiline, std::optional<std::string> text)
        : isMultiline(isMultiline), text(std::move(text)) {
        //
    }

    bool Comment::getIsMultiline() const {
        return this->isMultiline;
    }

    void Comment::setIsMultiline(bool isMultiline) {
        this->isMultiline = isMultiline;
    }

    std::optional<std::string> Comment::getText() const {
        return this->text;
    }

    void Comment::setText(std::optional<std::string> text) {
        this->text = std::move(text);
    }
}
