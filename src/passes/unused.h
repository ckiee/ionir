#pragma once

#include "misc/helpers.h"
#include "pass.h"

namespace ionir {
    class UnusedPass : public Pass {
    public:
        /**
         * Analyzes function calls and removes functions
         * that are not called or referenced.
         */
        void visitFunction(Ptr<Function> node) override;
    };
}
