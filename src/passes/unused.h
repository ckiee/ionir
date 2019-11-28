#pragma once

#include "pass.h"

namespace ionir
{
class UnusedPass : public Pass
{
public:
    /**
     * Analyzes function calls and removes functions
     * that are not called or referenced.
     */
    Node *visitFunction(Function *node) override;
};
} // namespace ionir
