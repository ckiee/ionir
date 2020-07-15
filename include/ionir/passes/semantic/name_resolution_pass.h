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
        Ptr<ionshared::StackTrace> stackTrace;

        std::list<PtrSymbolTable<Construct>> scope;

    public:
        explicit NameResolutionPass(Ptr<ionshared::StackTrace> stackTrace = std::make_shared<ionshared::StackTrace>());

        void visitModule(Ptr<Module> node) override;

        void visitScopeAnchor(Ptr<ScopeAnchor<>> node) override;

        void visitRef(PtrRef<> node) override;

        Ptr<ionshared::StackTrace> getStackTrace() const;

        const std::list<PtrSymbolTable<Construct>> &getScope() const;
    };
}
