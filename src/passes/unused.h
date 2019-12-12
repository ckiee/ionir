#pragma once

#include <memory>
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
    std::shared_ptr<Node> visitFunction(std::shared_ptr<Function> node) override;
};
} // namespace ionir
