#pragma once

#include <optional>
#include <llvm/IR/BasicBlock.h>
#include <ionir/misc/wrapper.h>
#include <ionir/misc/helpers.h>
#include "ir_builder.h"

namespace ionir {
    class LlvmBlock : public Wrapper<llvm::BasicBlock *> {
    private:
        std::optional<Ptr<IrBuilder>> cachedBuilder;

    public:
        explicit LlvmBlock(llvm::BasicBlock *value);

        Ptr<IrBuilder> getBuilder();
    };
}
