#pragma once

#include <optional>
#include <ionir/misc/helpers.h>
#include <ionir/passes/pass.h>

namespace ionir {
    /**
     * Resolves partial constructs which reference
     * undefined symbols at the time by their identifier(s).
     */
    class NameResolutionPass : public Pass {
    public:
    };
}
