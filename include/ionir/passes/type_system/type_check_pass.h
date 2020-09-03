#pragma once

#include <ionir/passes/pass.h>

namespace ionir {
    class TypeCheckPass : public Pass {
    public:
        void visitFunction(ionshared::Ptr<Function> node) override;

        void visitReturnStatement(ionshared::Ptr<ReturnStatement> node) override;

        void visitVariableDecl(ionshared::Ptr<VariableDecl> node) override;
    };
}
