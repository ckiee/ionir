#include <ionir/llvm/llvm_block.h>

namespace ionir {
    LlvmBlock::LlvmBlock(llvm::BasicBlock *value) : LlvmEntityWrapper(value), cachedBuilder(std::nullopt) {
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

    OptPtr<LlvmInst> LlvmBlock::findInstById(std::string id) {
        // TODO: Usage of auto keyword.
        auto llvmValueSymbolTable = this->value->getValueSymbolTable();

        // TODO: Find the inst in the Block's value symbol table.

        return std::nullopt;
    }
}
