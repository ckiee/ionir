#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    struct DeadCodeEliminationPass : public Pass {
        IONSHARED_PASS_ID;

        explicit DeadCodeEliminationPass(
            ionshared::Ptr<ionshared::PassContext> context
        );

        void visitBasicBlock(ionshared::Ptr<BasicBlock> node) override;

        // TODO: Optimize assignment to a dead variable (alloca but never used).
    };
}
