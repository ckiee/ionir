#include <ionir/llvm/llvm_block.h>

namespace ionir {
    LlvmBlock::LlvmBlock(llvm::BasicBlock *value) : SafeWrapper(value), cachedBuilder(std::nullopt) {
        //
    }

    Ptr<IrBuilder> LlvmBlock::getBuilder() {
        if (this->cachedBuilder.has_value()) {
            return *this->cachedBuilder;
        }

        this->cachedBuilder = std::make_shared<IrBuilder>(llvm::IRBuilder<>(this->value));

        return *this->cachedBuilder;
    }

    OptPtr<LlvmInst> LlvmBlock::findTerminatorInst() const {
        llvm::Instruction *llvmTerminatorInst = this->value->getTerminator();

        if (llvmTerminatorInst != nullptr) {
            return std::make_shared<LlvmInst>(llvmTerminatorInst);
        }

        return std::nullopt;
    }
}
