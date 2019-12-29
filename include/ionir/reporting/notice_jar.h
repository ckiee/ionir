#pragma once

#include <vector>
#include "notice.h"

namespace ionir {
    class NoticeJar : public Wrapper<std::vector<Notice>> {
    public:
        explicit NoticeJar(std::vector<Notice> value = {});

        std::vector<Notice> get() const;

        void put(Notice notice);
    };
}
