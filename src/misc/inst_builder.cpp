#include <ionir/misc/inst_builder.h>

namespace ionir {
    InstBuilder::InstBuilder(ionshared::Ptr<BasicBlock> basicBlock) : basicBlock(std::move(basicBlock)) {
        //
    }

    ionshared::Ptr<BasicBlock> InstBuilder::getSection() const {
        return this->basicBlock;
    }

    void InstBuilder::insert(const ionshared::Ptr<Inst> &inst) {
        this->basicBlock->getInsts().push_back(inst);
    }

    ionshared::Ptr<AllocaInst> InstBuilder::createAlloca(const std::string &id, ionshared::Ptr<Type> type) {
        ionshared::Ptr<AllocaInst> allocaInst = this->make<AllocaInst>(AllocaInstOpts{
            this->basicBlock,
            std::move(type)
        });

        this->basicBlock->insertInst(allocaInst);

        return allocaInst;
    }

    ionshared::Ptr<BranchInst> InstBuilder::createBranch(ionshared::Ptr<Construct> condition, PtrRef<BasicBlock> bodySection, PtrRef<BasicBlock> otherwiseSection) {
        return this->make<BranchInst>(BranchInstOpts{
            this->basicBlock,
            std::move(condition),
            std::move(bodySection),
            std::move(otherwiseSection)
        });
    }

    ionshared::Ptr<BranchInst> InstBuilder::createBranch(ionshared::Ptr<Construct> condition, const std::string &bodySectionId, const std::string &otherwiseSectionId) {
        PtrRef<BasicBlock> bodyBlock = std::make_shared<Ref<BasicBlock>>(bodySectionId, nullptr);
        PtrRef<BasicBlock> otherwiseBlock = std::make_shared<Ref<BasicBlock>>(otherwiseSectionId, nullptr);
        ionshared::Ptr<BranchInst> branchInst = this->createBranch(std::move(condition), bodyBlock, otherwiseBlock);

        bodyBlock->setOwner(branchInst);
        otherwiseBlock->setOwner(branchInst);

        return branchInst;
    }

    ionshared::Ptr<ReturnInst> InstBuilder::createReturn(const ionshared::OptPtr<Value<>> &value) {
        return this->make<ReturnInst, ReturnInstOpts>(ReturnInstOpts{
            this->basicBlock,
            value
        });
    }

    ionshared::Ptr<CallInst> InstBuilder::createCall(const ionshared::Ptr<BasicBlock> &basicBlock, OptPtrRef<Function> callee) {
        return this->make<CallInst>(CallInstOpts{
            this->basicBlock,
            std::move(callee)
        });
    }
}
