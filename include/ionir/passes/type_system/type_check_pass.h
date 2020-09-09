#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    class TypeCheckPass : public Pass {
    public:
        TypeCheckPass();

        void initialize(ionshared::PassInfo &info) override;

        void visitFunction(ionshared::Ptr<Function> node) override;

        void visitReturnInst(ionshared::Ptr<ReturnInst> node) override;

        void visitStoreInst(ionshared::Ptr<StoreInst> node) override;
    };
}
