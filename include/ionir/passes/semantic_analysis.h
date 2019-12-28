#pragma once

#include <ionir/construct/function.h>
#include <ionir/misc/helpers.h>
#include "pass.h"

namespace ionir {
    class SemanticAnalysisPass : public Pass {
    public:
        SemanticAnalysisPass();

        void functionReturnCheck(Ptr<Function> node);

        void visitFunction(Ptr<Function> node) override;
    };
}
