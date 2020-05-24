#include <ionir/llvm/llvm_inst.h>

namespace ionir {
    LlvmInst::LlvmInst(llvm::Instruction *value) : SafeWrapper(value) {
        //
    }

    std::string LlvmInst::getId() const {
        return this->value->getName();
    }
}
