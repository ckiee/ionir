#include <ionir/misc/inst_builder.h>
#include <ionir/construct/function_body.h>

namespace ionir {
    InstBuilder::InstBuilder(ionshared::Ptr<BasicBlock> basicBlock) :
        basicBlock(std::move(basicBlock)) {
        //
    }

    ionshared::Ptr<BasicBlock> InstBuilder::getSection() const {
        return this->basicBlock;
    }

    void InstBuilder::appendInst(const ionshared::Ptr<Inst> &inst) {
        this->basicBlock->getInsts().push_back(inst);
    }

    ionshared::Ptr<AllocaInst> InstBuilder::createAlloca(const std::string &id, ionshared::Ptr<Type> type) {
        return this->make<AllocaInst>(AllocaInstOpts{
            this->basicBlock,
            std::move(type)
        });
    }

    ionshared::Ptr<StoreInst> InstBuilder::createStore(ionshared::Ptr<Value<>> value, PtrRef<AllocaInst> target) {
        return this->make<StoreInst>(StoreInstOpts{
            this->basicBlock,
            std::move(value),
            std::move(target)
        });
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
        PtrRef<BasicBlock> consequentBasicBlock = std::make_shared<Ref<BasicBlock>>(bodySectionId, nullptr);
        PtrRef<BasicBlock> alternativeBasicBlock = std::make_shared<Ref<BasicBlock>>(otherwiseSectionId, nullptr);
        ionshared::Ptr<BranchInst> branchInst = this->createBranch(std::move(condition), consequentBasicBlock, alternativeBasicBlock);

        consequentBasicBlock->setOwner(branchInst);
        alternativeBasicBlock->setOwner(branchInst);

        return branchInst;
    }

    ionshared::Ptr<ReturnInst> InstBuilder::createReturn(const ionshared::OptPtr<Construct> &value) {
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

    ionshared::Ptr<JumpInst> InstBuilder::createJump(const PtrRef<BasicBlock> &basicBlockRef) {
        return this->make<JumpInst>(JumpInstOpts{
            this->basicBlock,

            std::make_shared<Ref<BasicBlock>>(
                basicBlock->getId(),

                // TODO: Should this be the correct owner? FunctionBody? or should it be Function? Probably FunctionBody, investigate as a precaution.
                this->basicBlock->getParent(),

                basicBlock
            )
        });
    }
}
