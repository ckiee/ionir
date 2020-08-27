#pragma once

#include <optional>
#include <string>

namespace ionir {
    class Comment {
    private:
        bool isMultiline;

        std::optional<std::string> text;

    public:
        Comment(bool isMultiline, std::optional<std::string> text);

        [[nodiscard]] bool getIsMultiline() const;

        void setIsMultiline(bool isMultiline);

        [[nodiscard]] std::optional<std::string> getText() const;

        void setText(std::optional<std::string> text);
    };
}
