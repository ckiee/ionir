#pragma once

#include "pass.h"
#include "pass_priority.h"

namespace ionir {
    struct PassManagerItem {
        Ptr<Pass> pass;

        PassPriority priority = PassPriority::Normal;
    };
}
