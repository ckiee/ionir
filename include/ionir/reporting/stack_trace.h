#pragma once

#include <optional>
#include <stack>
#include <iosfwd>
#include <string>
#include <ionir/container/stack.h>
#include <ionir/misc/wrapper.h>
#include "notice.h"

namespace ionir {
    class StackTrace : public Wrapper<Stack<Notice>> {
    public:
        explicit StackTrace();

        explicit StackTrace(Stack<Notice> value);

        explicit StackTrace(std::stack<Notice> value);

        Stack<Notice> getStack() const;

        void push(Notice notice);

        bool isEmpty() const;

        std::optional<std::string> make();
    };

    inline std::ostream &operator<<(std::ostream &stream, StackTrace &noticeJar) {
        return stream << noticeJar.make().value_or(nullptr);
    }
}
