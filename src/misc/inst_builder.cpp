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

    ionshared::Ptr<BranchInst> InstBuilder::createBranch(
        ionshared::Ptr<Construct> condition,
        const ionshared::Ptr<BasicBlock> &consequentBasicBlock,
        const ionshared::Ptr<BasicBlock> &alternativeBasicBlock
    ) {
        return this->createBranch(
            std::move(condition),
            std::make_shared<Ref<BasicBlock>>(consequentBasicBlock),
            std::make_shared<Ref<BasicBlock>>(alternativeBasicBlock)
        );
    }

    ionshared::Ptr<BranchInst> InstBuilder::createBranch(
        ionshared::Ptr<Construct> condition,
        PtrRef<BasicBlock> consequentBasicBlock,
        PtrRef<BasicBlock> alternativeBasicBlock
    ) {
        return this->make<BranchInst>(BranchInstOpts{
            this->basicBlock,
            std::move(condition),
            std::move(consequentBasicBlock),
            std::move(alternativeBasicBlock)
        });
    }

    ionshared::Ptr<BranchInst> InstBuilder::createBranch(
        ionshared::Ptr<Construct> condition,
        const std::string &consequentBasicBlockId,
        const std::string &alternativeBasicBlockId
    ) {
        PtrRef<BasicBlock> consequentBasicBlock = std::make_shared<Ref<BasicBlock>>(
            RefKind::BasicBlock,
            consequentBasicBlockId,
            nullptr
        );

        PtrRef<BasicBlock> alternativeBasicBlock = std::make_shared<Ref<BasicBlock>>(
            RefKind::BasicBlock,
            alternativeBasicBlockId,
            nullptr
        );

        ionshared::Ptr<BranchInst> branchInst = this->createBranch(
            std::move(condition),
            consequentBasicBlock,
            alternativeBasicBlock
        );

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

    ionshared::Ptr<CallInst> InstBuilder::createCall(
        PtrRef<Function> callee,
        std::vector<ionshared::Ptr<Construct>> args
    ) {
        return this->make<CallInst>(CallInstOpts{
            this->basicBlock,
            std::move(callee),
            std::move(args)
        });
    }

    ionshared::Ptr<JumpInst> InstBuilder::createJump(const PtrRef<BasicBlock> &basicBlockRef) {
        return this->make<JumpInst>(JumpInstOpts{
            this->basicBlock,
            basicBlockRef
        });
    }
}
