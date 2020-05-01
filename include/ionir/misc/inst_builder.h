#pragma once

#include <ionir/construct/inst.h>
#include <ionir/construct/section.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/inst/call.h>
#include "helpers.h"

namespace ionir {
    class InstBuilder {
    private:
        Ptr<Section> section;

    public:
        InstBuilder(Ptr<Section> section);

        Ptr<Section> getSection() const;

        void insert(Ptr<Inst> inst);

        template<class TInst, typename... TArgs>
        Ptr<TInst> make(TArgs... args) {
            // TODO: Ensure T inherits from Inst or derived.

            Ptr<TInst> inst = std::make_shared<TInst>(args...);

            this->insert(inst);

            return inst;
        }

        Ptr<AllocaInst> createAlloca(std::string id, Ptr<Type> type);

        Ptr<BranchInst> createBranch(Ptr<Expr<>> condition, PtrRef<Section> bodySection, PtrRef<Section> otherwiseSection);

        Ptr<BranchInst> createBranch(Ptr<Expr<>> condition, std::string bodySectionId, std::string otherwiseSectionId);

        Ptr<ReturnInst> createReturn(OptPtr<Value<>> value = std::nullopt);

        Ptr<CallInst> createCall(Ptr<Section> section, OptPtrRef<Function> callee = std::nullopt, std::optional<std::string> yieldId = std::nullopt);
    };
}
