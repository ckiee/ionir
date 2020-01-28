#include <ionir/passes/semantic/construct_validation_pass.h>

namespace ionir {
    void ConstructValidationPass::visit(Ptr<Construct> node) {
        if (!node->verify()) {
            // TODO: Append to stack trace instead of raising an error.
            throw std::runtime_error("Unable to validate node");
        }
    }
}
