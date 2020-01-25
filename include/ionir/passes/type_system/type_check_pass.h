#pragma once

#include "ionir/passes/pass.h"

namespace ionir {
    class TypeCheckPass : public Pass {
    public:
        void visitFunction(Ptr <Function> node) override;

        void visitStoreInst(Ptr<StoreInst> node) override;
    };
}
