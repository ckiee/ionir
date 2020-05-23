#pragma once

#include <llvm/IR/Instruction.h>
#include <ionir/misc/wrapper.h>
#include "llvm_entity_wrapper.h"

namespace ionir {
    class LlvmInst : public LlvmEntityWrapper<llvm::Instruction *> {
    public:
        explicit LlvmInst(llvm::Instruction *value);

        std::string getId() const;
    };
}
