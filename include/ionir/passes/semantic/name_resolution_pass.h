#pragma once

#include <ionshared/error_handling/notice.h>
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
        ionshared::Ptr<ionshared::NoticeStack> noticeStack;

        std::list<PtrSymbolTable<Construct>> scope;

    public:
        explicit NameResolutionPass(
            ionshared::Ptr<ionshared::NoticeStack> noticeStack =
                std::make_shared<ionshared::NoticeStack>()
        );

        void visitModule(ionshared::Ptr<Module> node) override;

        void visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node) override;

        void visitRef(PtrRef<> node) override;

        [[nodiscard]] ionshared::Ptr<ionshared::NoticeStack> getNoticeStack() const;

        [[nodiscard]] const std::list<PtrSymbolTable<Construct>> &getScope() const;
    };
}
