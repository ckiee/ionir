#include <ionir/misc/inst_builder.h>

namespace ionir {
    InstBuilder::InstBuilder(Ptr<BasicBlock> basicBlock) : basicBlock(basicBlock) {
        //
    }

    Ptr<BasicBlock> InstBuilder::getSection() const {
        return this->basicBlock;
    }

    void InstBuilder::insert(Ptr<Inst> inst) {
        this->basicBlock->getInsts().push_back(inst);
    }

    Ptr<AllocaInst> InstBuilder::createAlloca(std::string id, Ptr<Type> type) {
        Ptr<AllocaInst> allocaInst = this->make<AllocaInst>(AllocaInstOpts{
            this->basicBlock,
            id,
            type
        });

        this->basicBlock->insertInst(allocaInst);

        return allocaInst;
    }

    Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr<>> condition, PtrRef<BasicBlock> bodySection, PtrRef<BasicBlock> otherwiseSection) {
        return this->make<BranchInst>(BranchInstOpts{
            this->basicBlock,
            condition,
            bodySection,
            otherwiseSection
        });
    }

    Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr<>> condition, std::string bodySectionId, std::string otherwiseSectionId) {
        PtrRef<BasicBlock> bodyBlock = std::make_shared<Ref<BasicBlock>>(bodySectionId, nullptr);
        PtrRef<BasicBlock> otherwiseBlock = std::make_shared<Ref<BasicBlock>>(otherwiseSectionId, nullptr);
        Ptr<BranchInst> branchInst = this->createBranch(condition, bodyBlock, otherwiseBlock);

        bodyBlock->setOwner(branchInst);
        otherwiseBlock->setOwner(branchInst);

        return branchInst;
    }

    Ptr<ReturnInst> InstBuilder::createReturn(OptPtr<Value<>> value) {
        return this->make<ReturnInst, ReturnInstOpts>(ReturnInstOpts{
            this->basicBlock,
            value
        });
    }

    Ptr<CallInst> InstBuilder::createCall(Ptr<BasicBlock> basicBlock, OptPtrRef<Function> callee, std::optional<std::string> yieldId) {
        return this->make<CallInst>(CallInstOpts{
            this->basicBlock,
            yieldId,
            callee
        });
    }
}
