#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    class ConstructValidationPass : public Pass {
    public:
        IONSHARED_PASS_ID;

        explicit ConstructValidationPass(
            ionshared::Ptr<ionshared::PassContext> context
        );

        void visit(ionshared::Ptr<Construct> node) override;
    };
}
