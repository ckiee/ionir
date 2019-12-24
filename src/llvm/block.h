#pragma once

#include <optional>
#include <llvm/IR/BasicBlock.h>
#include "misc/wrapper.h"
#include "misc/helpers.h"
#include "ir_builder.h"

namespace ionir {
    class Block : public Wrapper<llvm::BasicBlock *> {
    private:
        std::optional<Ptr<IrBuilder>> cachedBuilder;

    public:
        explicit Block(llvm::BasicBlock *value);

        Ptr<IrBuilder> getBuilder();
    };
}
