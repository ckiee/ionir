#include <ionir/passes/pass.h>

namespace ionir {
    JumpInst::JumpInst(const JumpInstOpts &opts)
        : Inst(opts.parent, InstKind::Jump), blockRef(opts.blockRef) {
        //
    }

    void JumpInst::accept(Pass &visitor) {
        visitor.visitBranchInst(this->dynamicCast<BranchInst>());
    }

    Ast JumpInst::getChildNodes() {
        // TODO: Should have no children, function bodies should be LINEAR! BRANCH defines inline block! WRONG!
        return {
            this->blockRef
        };
    }

    PtrRef<BasicBlock> JumpInst::getBlockRef() const {
        return this->blockRef;
    }

    void JumpInst::setBlockRef(PtrRef<BasicBlock> blockRef) {
        this->blockRef = std::move(blockRef);
        this->blockRef->setOwner(this->getPtr());
    }
}
