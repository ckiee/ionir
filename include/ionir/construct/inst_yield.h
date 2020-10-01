#pragma once

#include <optional>
#include <string>
#include "inst.h"

namespace ionir {
    struct InstYieldOpts : InstOpts {
        std::string yieldId;
    };

    struct InstYield {
        std::string yieldId;

        explicit InstYield(std::string yieldId);
    };
}
