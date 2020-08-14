#include <ionir/construct/inst_yield.h>

namespace ionir {
    InstYield::InstYield(std::optional<std::string> yieldId) : yieldId(std::move(yieldId)) {
        //
    }

    std::optional<std::string> InstYield::getYieldId() const noexcept {
        return this->yieldId;
    }

    void InstYield::setYieldId(std::optional<std::string> yieldId) noexcept {
        this->yieldId = std::move(yieldId);
    }
}
