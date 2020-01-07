#include <ionir/llvm/llvm_block.h>

namespace ionir {
    LlvmBlock::LlvmBlock(llvm::BasicBlock *value) : Wrapper(value), cachedBuilder(std::nullopt) {
        //
    }

    Ptr<IrBuilder> LlvmBlock::getBuilder() {
        if (this->cachedBuilder.has_value()) {
            return *this->cachedBuilder;
        }

        this->cachedBuilder =
            std::make_shared<IrBuilder>(llvm::IRBuilder<>(this->value));

        return *this->cachedBuilder;
    }
}
