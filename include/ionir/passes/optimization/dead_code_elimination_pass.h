#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    class DeadCodeEliminationPass : public Pass {
    public:
        void visitBasicBlock(Ptr<BasicBlock> node) override;
    };
}
