#pragma once

#include <memory>
#include "misc/helpers.h"
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
    Ptr<Node> visitFunction(Ptr<Function> node) override;
};
} // namespace ionir
