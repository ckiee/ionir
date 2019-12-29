#include <ionir/misc/wrapper.h>
#include <ionir/reporting/notice_jar.h>

namespace ionir {
    NoticeJar::NoticeJar(std::vector<Notice> value) : Wrapper<std::vector<Notice>>(value) {
        //
    }

    std::vector<Notice> NoticeJar::get() const {
        return this->value;
    }
}
