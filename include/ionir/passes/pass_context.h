#pragma once

#include <ionshared/error_handling/notice.h>
#include <ionshared/error_handling/diagnostic_builder.h>

namespace ionir {
    class PassContext {
    private:
        ionshared::Ptr<ionshared::NoticeStack> noticeStack;

        ionshared::Ptr<ionshared::DiagnosticBuilder> diagnosticBuilder;

    public:
        explicit PassContext(const ionshared::Ptr<ionshared::NoticeStack> &noticeStack);

        [[nodiscard]] ionshared::Ptr<ionshared::NoticeStack> getNoticeStack() const noexcept;

        [[nodiscard]] ionshared::Ptr<ionshared::DiagnosticBuilder> getDiagnosticBuilder() const noexcept;
    };
}
