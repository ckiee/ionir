#include <ionir/passes/pass.h>

namespace ionir {
    BranchInst::BranchInst(BranchInstOpts opts)
        : Inst(opts.parent, InstKind::Branch), condition(opts.condition), bodySectionRef(opts.bodyRef), otherwiseSectionRef(opts.otherwiseRef) {
        //
    }

    void BranchInst::accept(Pass &visitor) {
        visitor.visitBranchInst(this->dynamicCast<BranchInst>());
    }

    Ast BranchInst::getChildNodes() const {
        // TODO: What about condition?

        return {
            this->bodySectionRef,
            this->otherwiseSectionRef
        };
    }

    Ptr<Expr<>> BranchInst::getCondition() const {
        return this->condition;
    }

    void BranchInst::setCondition(Ptr<Expr<>> condition) {
        this->condition = condition;
    }

    PtrRef<BasicBlock> BranchInst::getBodyRef() const {
        return this->bodySectionRef;
    }

    void BranchInst::setBodyRef(PtrRef<BasicBlock> bodyRef) {
        this->bodySectionRef = bodyRef;
        this->bodySectionRef->setOwner(this->getPtr());
    }

    PtrRef<BasicBlock> BranchInst::getOtherwiseRef() const {
        return this->otherwiseSectionRef;
    }

    void BranchInst::setOtherwiseRef(PtrRef<BasicBlock> otherwiseRef) {
        this->otherwiseSectionRef = otherwiseRef;
        this->otherwiseSectionRef->setOwner(this->getPtr());
    }
}
