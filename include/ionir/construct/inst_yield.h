#pragma once

#include <optional>
#include <string>
#include "inst.h"

namespace ionir {
    struct InstYieldOpts : InstOpts {
        std::string yieldId;
    };

    class InstYield {
    private:
        std::string yieldId;

    public:
        explicit InstYield(std::string yieldId);

        [[nodiscard]] std::string getYieldId() const noexcept;

        void setYieldId(std::string yieldId) noexcept;
    };
}
