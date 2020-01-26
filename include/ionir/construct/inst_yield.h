#pragma once

#include <string>
#include "inst.h"

namespace ionir {
    class InstYield {
    private:
        std::string yieldId;

    public:
        explicit InstYield(std::string yieldId);

        std::string getYieldId() const;

        void setYieldId(std::string yieldId);
    };
}
