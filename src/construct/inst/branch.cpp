#include <ionir/passes/pass.h>

namespace ionir {
    BranchInst::BranchInst(BranchInstOpts opts)
        : Inst(opts.parent, InstKind::Branch), condition(opts.condition), bodyRef(opts.bodyRef), otherwiseRef(opts.otherwiseRef) {
        //
    }

    void BranchInst::accept(Pass &visitor) {
        visitor.visitBranchInst(this->cast<BranchInst>());
    }

    Ast BranchInst::getChildNodes() const {
        Ast children = {
            this->bodyRef
        };

        if (this->otherwiseRef.has_value()) {
            children.push_back(*this->otherwiseRef);
        }

        return children;
    }

    Ptr<Expr<>> BranchInst::getCondition() const {
        return this->condition;
    }

    void BranchInst::setCondition(Ptr<Expr<>> condition) {
        this->condition = condition;
    }

    PtrRef<Section> BranchInst::getBodyRef() const {
        return this->bodyRef;
    }

    void BranchInst::setBodyRef(PtrRef<Section> bodyRef) {
        this->bodyRef = bodyRef;
        this->bodyRef->setOwner(this->getPtr());
    }

    OptPtrRef<Section> BranchInst::getOtherwiseRef() const {
        return this->otherwiseRef;
    }

    void BranchInst::setOtherwiseRef(OptPtrRef<Section> otherwiseRef) {
        this->otherwiseRef = otherwiseRef;

        if (this->otherwiseRef.has_value()) {
            this->otherwiseRef->get()->setOwner(this->getPtr());
        }
    }
}
