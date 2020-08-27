#include <ionir/error_handling/notice_sentinel.h>

namespace ionir {
    NoticeSentinel::NoticeSentinel(ionshared::Ptr<ionshared::NoticeStack> noticeStack) :
        noticeStack(std::move(noticeStack)) {
        //
    }

    ionshared::Ptr<ionshared::NoticeStack> NoticeSentinel::getNoticeStack() const noexcept {
        return this->noticeStack;
    }
}
