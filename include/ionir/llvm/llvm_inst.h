#pragma once

#include <llvm/IR/Instruction.h>
#include <ionir/misc/wrapper.h>
#include "ionir/misc/safe_wrapper.h"

namespace ionir {
    class LlvmInst : public SafeWrapper<llvm::Instruction *> {
    public:
        explicit LlvmInst(llvm::Instruction *value);

        std::string getId() const;
    };
}
