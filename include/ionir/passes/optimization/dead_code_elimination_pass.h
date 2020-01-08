#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    class DeadCodeEliminationPass : public Pass {
    public:
        void visitSection(Ptr<Section> node) override;
    };
}
