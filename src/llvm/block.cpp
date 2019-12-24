#include "block.h"

namespace ionir {
    Block::Block(llvm::BasicBlock *value) : Wrapper(value), cachedBuilder(std::nullopt) {
        //
    }

    Ptr<IrBuilder> Block::getBuilder() {
        if (this->cachedBuilder.has_value()) {
            return *this->cachedBuilder;
        }

        this->cachedBuilder =
                std::make_shared<IrBuilder>(llvm::IRBuilder<>(this->value));

        return *this->cachedBuilder;
    }
}
