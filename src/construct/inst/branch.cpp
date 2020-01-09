#include <ionir/passes/pass.h>

namespace ionir {
    BranchInst::BranchInst(BranchInstOpts opts)
        : Inst(opts.parent, InstKind::Branch), condition(opts.condition), body(opts.body), otherwise(opts.otherwise) {
        //
    }

    void BranchInst::accept(Pass &visitor) {
        visitor.visitBranchInst(this->cast<BranchInst>());
    }

    Ptr<Expr> BranchInst::getCondition() const {
        return this->condition;
    }

    void BranchInst::setCondition(Ptr<Expr> condition) {
        this->condition = condition;
    }

    PtrRef<Section> BranchInst::getBody() const {
        return this->body;
    }

    void BranchInst::setBody(PtrRef<Section> body) {
        this->body = body;
    }

    OptPtrRef<Section> BranchInst::getOtherwise() const {
        return this->otherwise;
    }

    void BranchInst::setOtherwise(OptPtrRef<Section> otherwise) {
        this->otherwise = otherwise;
    }
}
