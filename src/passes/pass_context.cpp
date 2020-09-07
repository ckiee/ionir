#include <ionir/passes/pass_context.h>

namespace ionir {
    PassContext::PassContext(const ionshared::Ptr<ionshared::NoticeStack> &noticeStack) :
        noticeStack(noticeStack),
        diagnosticBuilder(std::make_shared<ionshared::DiagnosticBuilder>(noticeStack)) {
        //
    }

    ionshared::Ptr<ionshared::NoticeStack> PassContext::getNoticeStack() const noexcept {
        return this->noticeStack;
    }

    ionshared::Ptr<ionshared::DiagnosticBuilder> PassContext::getDiagnosticBuilder() const noexcept {
        return this->diagnosticBuilder;
    }
}
