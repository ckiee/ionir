#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    class DeadCodeEliminationPass : public Pass {
    public:
        void visitBasicBlock(ionshared::Ptr<BasicBlock> node) override;
    };
}
