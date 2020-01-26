#include <ionir/construct/inst_yield.h>

namespace ionir {
    InstYield::InstYield(std::string yieldId) : yieldId(yieldId) {
        //
    }

    std::string InstYield::getYieldId() const {
        return this->yieldId;
    }

    void InstYield::setYieldId(std::string yieldId) {
        this->yieldId = yieldId;
    }
}
