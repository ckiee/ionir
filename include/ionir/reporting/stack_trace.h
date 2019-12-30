#pragma once

#include <iosfwd>
#include <string>
#include <ionir/container/stack.h>
#include <ionir/misc/wrapper.h>
#include "notice.h"

namespace ionir {
    class StackTrace : public Wrapper<Stack<Notice>> {
    public:
        explicit StackTrace(Stack<Notice> value = {});

        Stack<Notice> get() const;

        void put(Notice notice);

        std::string make();
    };

    inline std::ostream &operator<<(std::ostream &stream, StackTrace &noticeJar) {
        return stream << noticeJar.make();
    }
}
