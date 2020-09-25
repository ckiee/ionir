#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    // TODO
    struct BorrowCheckPass : public Pass {
        IONSHARED_PASS_ID;

        explicit BorrowCheckPass(
            ionshared::Ptr<ionshared::PassContext> context
        );
    };
}
