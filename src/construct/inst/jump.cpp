#include <ionir/passes/pass.h>

namespace ionir {
    JumpInst::JumpInst(const JumpInstOpts &opts) :
        Inst(opts.parent, InstKind::Jump),
        basicBlockTarget(opts.basicBlockTarget) {
        //
    }

    void JumpInst::accept(Pass &visitor) {
        visitor.visitBranchInst(this->dynamicCast<BranchInst>());
    }

    Ast JumpInst::getChildrenNodes() {
        // TODO: Should have no children, function bodies should be LINEAR! BRANCH defines inline block! WRONG!
        return {
            this->basicBlockTarget
        };
    }

    ionshared::Ptr<BasicBlock> JumpInst::getBasicBlockTarget() const noexcept {
        return this->basicBlockTarget;
    }

    void JumpInst::setBasicBlockTarget(ionshared::Ptr<BasicBlock> basicBlockTarget) noexcept {
        this->basicBlockTarget = std::move(basicBlockTarget);
    }
}
