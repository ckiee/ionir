#include <ionir/passes/pass.h>

namespace ionir {
    BranchInst::BranchInst(BranchInstOpts opts)
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

    Ptr<Construct> BranchInst::getCondition() const {
        return this->condition;
    }

    void BranchInst::setCondition(Ptr<Construct> condition) {
        this->condition = condition;
    }

    PtrRef<BasicBlock> BranchInst::getBlockRef() const {
        return this->blockRef;
    }

    void BranchInst::setBlockRef(PtrRef<BasicBlock> blockRef) {
        this->blockRef = blockRef;
        this->blockRef->setOwner(this->getPtr());
    }

    PtrRef<BasicBlock> BranchInst::getOtherwiseBlockRef() const {
        return this->otherwiseBlockRef;
    }

    void BranchInst::setOtherwiseBlockRef(PtrRef<BasicBlock> otherwiseBlockRef) {
        this->otherwiseBlockRef = otherwiseBlockRef;
        this->otherwiseBlockRef->setOwner(this->getPtr());
    }
}
