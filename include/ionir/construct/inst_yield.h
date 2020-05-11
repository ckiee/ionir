#pragma once

#include <optional>
#include <string>
#include "inst.h"

namespace ionir {
    class InstYield {
    private:
        std::optional<std::string> yieldId;

    public:
        explicit InstYield(std::optional<std::string> yieldId);

        std::optional<std::string> getYieldId() const;

        void setYieldId(std::optional<std::string> yieldId);
    };
}
