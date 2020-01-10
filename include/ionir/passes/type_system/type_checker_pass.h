#pragma once

#include "ionir/passes/pass.h"

namespace ionir {
    class TypeCheckerPass : public Pass {
    public:
        void visitFunction(Ptr <Function> node) override;
    };
}
