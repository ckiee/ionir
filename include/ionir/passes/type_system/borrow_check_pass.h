#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    // TODO
    class BorrowCheckPass : public Pass {
    public:
        IONSHARED_PASS_ID;

        BorrowCheckPass();
    };
}
