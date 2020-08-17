#pragma once

#include <ionshared/reporting/notice.h>
#include <ionir/construct/pseudo/error_marker.h>
#include <ionir/syntax/ast_result.h>

namespace ionir {
    class NoticeSentinel {
    private:
        ionshared::NoticeStack noticeStack;

    public:
        explicit NoticeSentinel(
            ionshared::NoticeStack noticeStack =
                std::make_shared<ionshared::Stack<ionshared::Notice>>()
        );

        [[nodiscard]] ionshared::NoticeStack getNoticeStack() const noexcept;

        template<typename T>
        AstPtrResult<T> makeError(std::string message) {
            // TODO: Review.
            return std::make_shared<ErrorMarker>(message);
        }
    };
}
