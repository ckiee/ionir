#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    class ConstructValidationPass : public Pass {
    public:
        void visit(ionshared::Ptr<Construct> node) override;
    };
}
