#pragma once

#include "ionir/passes/pass.h"

namespace ionir {
    class TypeCheckPass : public Pass {
    public:
        void visitFunction(ionshared::Ptr<Function> node) override;

        void visitStoreInst(ionshared::Ptr<StoreInst> node) override;
    };
}
