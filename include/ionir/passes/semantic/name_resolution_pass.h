#pragma once

#include <ionshared/reporting/notice.h>
#include <ionir/misc/helpers.h>
#include <ionir/passes/pass.h>
#include <ionir/tracking/symbol_table.h>

namespace ionir {
    /**
     * Resolves partial constructs which reference
     * undefined symbols at the time by their identifier(s).
     */
    class NameResolutionPass : public Pass {
    private:
        ionshared::Ptr<ionshared::StackTrace> stackTrace;

        std::list<PtrSymbolTable<Construct>> scope;

    public:
        explicit NameResolutionPass(ionshared::Ptr<ionshared::StackTrace> stackTrace = std::make_shared<ionshared::StackTrace>());

        void visitModule(ionshared::Ptr<Module> node) override;

        void visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node) override;

        void visitRef(PtrRef<> node) override;

        ionshared::Ptr<ionshared::StackTrace> getStackTrace() const;

        const std::list<PtrSymbolTable<Construct>> &getScope() const;
    };
}
