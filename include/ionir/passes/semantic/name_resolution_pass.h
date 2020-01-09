#pragma once

#include <optional>
#include <ionir/misc/helpers.h>
#include <ionir/passes/pass.h>
#include <ionir/reporting/notice.h>

namespace ionir {
    /**
     * Resolves partial constructs which reference
     * undefined symbols at the time by their identifier(s).
     */
    class NameResolutionPass : public Pass {
    private:
        Ptr<StackTrace> stackTrace;

    public:
        NameResolutionPass(Ptr<StackTrace> stackTrace = std::make_shared<StackTrace>());

        void visitRef(PtrRef<> node) override;

        Ptr<StackTrace> getStackTrace() const;
    };
}
