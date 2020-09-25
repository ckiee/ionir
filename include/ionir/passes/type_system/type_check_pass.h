#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    struct TypeCheckPass : public Pass {
        IONSHARED_PASS_ID;

        explicit TypeCheckPass(ionshared::Ptr<ionshared::PassContext> context);

        void initialize(ionshared::PassInfo &info) override;

        void visitFunction(ionshared::Ptr<Function> node) override;

        void visitReturnInst(ionshared::Ptr<ReturnInst> node) override;

        void visitStoreInst(ionshared::Ptr<StoreInst> node) override;
    };
}
