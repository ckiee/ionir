#include <ionir/passes/pass.h>

namespace ionir {
    BranchInst::BranchInst(const BranchInstOpts &opts) :
        Inst(opts.parent, InstKind::Branch),
        condition(opts.condition),
        consequentBasicBlock(opts.consequentBasicBlock),
        alternativeBasicBlock(opts.alternativeBasicBlock) {
        //
    }

    void BranchInst::accept(Pass &visitor) {
        visitor.visitBranchInst(this->dynamicCast<BranchInst>());
    }

    Ast BranchInst::getChildrenNodes() {
        // TODO: What about condition?

        return {
            this->consequentBasicBlock,
            this->alternativeBasicBlock
        };
    }

    ionshared::Ptr<Construct> BranchInst::getCondition() const noexcept {
        return this->condition;
    }

    void BranchInst::setCondition(ionshared::Ptr<Construct> condition) noexcept {
        this->condition = std::move(condition);
    }

    ionshared::Ptr<BasicBlock> BranchInst::getConsequentBasicBlock() const noexcept {
        return this->consequentBasicBlock;
    }

    void BranchInst::setConsequentBasicBlock(ionshared::Ptr<BasicBlock> consequentBasicBlock) noexcept {
        this->consequentBasicBlock = std::move(consequentBasicBlock);
    }

    ionshared::Ptr<BasicBlock> BranchInst::getAlternativeBasicBlock() const noexcept {
        return this->alternativeBasicBlock;
    }

    void BranchInst::setAlternativeBasicBlock(ionshared::Ptr<BasicBlock> alternativeBasicBlock) noexcept {
        this->alternativeBasicBlock = std::move(alternativeBasicBlock);
    }
}
