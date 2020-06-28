#pragma once

#include <ionir/construct/inst.h>
#include <ionir/construct/basic_block.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/inst/call.h>
#include "helpers.h"

namespace ionir {
    class InstBuilder {
    private:
        Ptr<BasicBlock> basicBlock;

    public:
        InstBuilder(Ptr<BasicBlock> basicBlock);

        Ptr<BasicBlock> getSection() const;

        void insert(Ptr<Inst> inst);

        template<class TInst, typename... TArgs>
        Ptr<TInst> make(TArgs... args) {
            // TODO: Ensure T inherits from Inst or derived.

            Ptr<TInst> inst = std::make_shared<TInst>(args...);

            this->insert(inst);

            return inst;
        }

        Ptr<AllocaInst> createAlloca(std::string id, Ptr<Type> type);

        Ptr<BranchInst> createBranch(Ptr<Construct> condition, PtrRef<BasicBlock> bodySection, PtrRef<BasicBlock> otherwiseSection);

        Ptr<BranchInst> createBranch(Ptr<Construct> condition, std::string bodySectionId, std::string otherwiseSectionId);

        Ptr<ReturnInst> createReturn(OptPtr<Value<>> value = std::nullopt);

        Ptr<CallInst> createCall(Ptr<BasicBlock> basicBlock, OptPtrRef<Function> callee = std::nullopt);
    };
}
