#include <ionir/passes/pass.h>

namespace ionir {
    BranchInst::BranchInst(const BranchInstOpts &opts) :
        Inst(opts.parent, InstKind::Branch),
        condition(opts.condition),
        consequentBlockRef(opts.blockRef),
        alternativeBlockRef(opts.otherwiseRef) {
        //
    }

    void BranchInst::accept(Pass &visitor) {
        visitor.visitBranchInst(this->dynamicCast<BranchInst>());
    }

    Ast BranchInst::getChildNodes() {
        // TODO: What about condition?

        return {
            this->consequentBlockRef,
            this->alternativeBlockRef
        };
    }

    ionshared::Ptr<Construct> BranchInst::getCondition() const {
        return this->condition;
    }

    void BranchInst::setCondition(ionshared::Ptr<Construct> condition) {
        this->condition = std::move(condition);
    }

    PtrRef<BasicBlock> BranchInst::getConsequentBasicBlockRef() const {
        return this->consequentBlockRef;
    }

    void BranchInst::setConsequentBlockRef(PtrRef<BasicBlock> blockRef) {
        this->consequentBlockRef = std::move(blockRef);
        this->consequentBlockRef->setOwner(this->getPtr());
    }

    PtrRef<BasicBlock> BranchInst::getAlternativeBasicBlockRef() const {
        return this->alternativeBlockRef;
    }

    void BranchInst::setAlternativeBlockRef(PtrRef<BasicBlock> otherwiseBlockRef) {
        this->alternativeBlockRef = std::move(otherwiseBlockRef);
        this->alternativeBlockRef->setOwner(this->getPtr());
    }
}
