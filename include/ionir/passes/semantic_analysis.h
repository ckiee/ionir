#pragma once

#include <optional>
#include <ionir/construct/function.h>
#include <ionir/misc/helpers.h>
#include "pass.h"

namespace ionir {
    /**
     * Performs semantic analysis on the AST.
     * Assumes that all partial constructs have
     * been resolved, and are registered on their
     * corresponding symbol table(s).
     */
    class SemanticAnalysisPass : public Pass {
    public:
        static std::optional<Ptr<Type>> evaluateExprType(Ptr<Expr> expr);

        SemanticAnalysisPass();

        void functionReturnCheck(Ptr<Function> node);

        void visitFunction(Ptr<Function> node) override;
    };
}
