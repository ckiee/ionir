#include <ionir/misc/inst_builder.h>

namespace ionir {
    InstBuilder::InstBuilder(ionshared::Ptr<BasicBlock> basicBlock) : basicBlock(basicBlock) {
        //
    }

    ionshared::Ptr<BasicBlock> InstBuilder::getSection() const {
        return this->basicBlock;
    }

    void InstBuilder::insert(ionshared::Ptr<Inst> inst) {
        this->basicBlock->getInsts().push_back(inst);
    }

    ionshared::Ptr<AllocaInst> InstBuilder::createAlloca(std::string id, ionshared::Ptr<Type> type) {
        ionshared::Ptr<AllocaInst> allocaInst = this->make<AllocaInst>(AllocaInstOpts{
            this->basicBlock,
            type
        });

        this->basicBlock->insertInst(allocaInst);

        return allocaInst;
    }

    ionshared::Ptr<BranchInst> InstBuilder::createBranch(ionshared::Ptr<Construct> condition, PtrRef<BasicBlock> bodySection, PtrRef<BasicBlock> otherwiseSection) {
        return this->make<BranchInst>(BranchInstOpts{
            this->basicBlock,
            condition,
            bodySection,
            otherwiseSection
        });
    }

    ionshared::Ptr<BranchInst> InstBuilder::createBranch(ionshared::Ptr<Construct> condition, std::string bodySectionId, std::string otherwiseSectionId) {
        PtrRef<BasicBlock> bodyBlock = std::make_shared<Ref<BasicBlock>>(bodySectionId, nullptr);
        PtrRef<BasicBlock> otherwiseBlock = std::make_shared<Ref<BasicBlock>>(otherwiseSectionId, nullptr);
        ionshared::Ptr<BranchInst> branchInst = this->createBranch(condition, bodyBlock, otherwiseBlock);

        bodyBlock->setOwner(branchInst);
        otherwiseBlock->setOwner(branchInst);

        return branchInst;
    }

    ionshared::Ptr<ReturnInst> InstBuilder::createReturn(ionshared::OptPtr<Value<>> value) {
        return this->make<ReturnInst, ReturnInstOpts>(ReturnInstOpts{
            this->basicBlock,
            value
        });
    }

    ionshared::Ptr<CallInst> InstBuilder::createCall(ionshared::Ptr<BasicBlock> basicBlock, OptPtrRef<Function> callee) {
        return this->make<CallInst>(CallInstOpts{
            this->basicBlock,
            callee
        });
    }
}
