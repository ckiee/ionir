#include <ionir/passes/pass.h>

#include <utility>

namespace ionir {
    BranchInst::BranchInst(const BranchInstOpts &opts)
        : Inst(opts.parent, InstKind::Branch), condition(opts.condition), blockRef(opts.blockRef), otherwiseBlockRef(opts.otherwiseRef) {
        //
    }

    void BranchInst::accept(Pass &visitor) {
        visitor.visitBranchInst(this->dynamicCast<BranchInst>());
    }

    Ast BranchInst::getChildNodes() {
        // TODO: What about condition?

        return {
            this->blockRef,
            this->otherwiseBlockRef
        };
    }

    ionshared::Ptr<Construct> BranchInst::getCondition() const {
        return this->condition;
    }

    void BranchInst::setCondition(ionshared::Ptr<Construct> condition) {
        this->condition = std::move(condition);
    }

    PtrRef<BasicBlock> BranchInst::getBlockRef() const {
        return this->blockRef;
    }

    void BranchInst::setBlockRef(PtrRef<BasicBlock> blockRef) {
        this->blockRef = std::move(blockRef);
        this->blockRef->setOwner(this->getPtr());
    }

    PtrRef<BasicBlock> BranchInst::getOtherwiseBlockRef() const {
        return this->otherwiseBlockRef;
    }

    void BranchInst::setOtherwiseBlockRef(PtrRef<BasicBlock> otherwiseBlockRef) {
        this->otherwiseBlockRef = std::move(otherwiseBlockRef);
        this->otherwiseBlockRef->setOwner(this->getPtr());
    }
}
