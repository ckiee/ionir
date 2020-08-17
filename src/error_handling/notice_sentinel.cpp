#include <ionir/error_handling/notice_sentinel.h>

namespace ionir {
    NoticeSentinel::NoticeSentinel(ionshared::NoticeStack noticeStack)
        : noticeStack(std::move(noticeStack)) {
        //
    }

    ionshared::NoticeStack NoticeSentinel::getNoticeStack() const noexcept {
        return this->noticeStack;
    }
}
