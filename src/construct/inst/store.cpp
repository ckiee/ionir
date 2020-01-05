#include <ionir/passes/pass.h>

namespace ionir {
    StoreInst::StoreInst(StoreInstOpts opts)
        : PartialInst(PartialInstOpts<StoreInstPartials>{
        opts.parent,

        StoreInstPartials{
            // TODO
        },

        InstKind::Branch
    }) {
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

    Ptr<Section> BranchInst::getBody() const {
        return this->body;
    }

    void BranchInst::setBody(Ptr<Section> body) {
        this->body = body;
    }

    std::optional<Ptr<Section>> BranchInst::getOtherwise() const {
        return this->otherwise;
    }

    void BranchInst::setOtherwise(std::optional<Ptr<Section>> otherwise) {
        this->otherwise = otherwise;
    }
}
