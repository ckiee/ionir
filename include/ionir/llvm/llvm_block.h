#pragma once

#include <optional>
#include <llvm/IR/BasicBlock.h>
#include <ionir/misc/wrapper.h>
#include <ionir/misc/helpers.h>
#include "ir_builder.h"
#include "llvm_inst.h"
#include "llvm_entity_wrapper.h"

namespace ionir {
    class LlvmBlock : public LlvmEntityWrapper<llvm::BasicBlock *> {
    private:
        OptPtr<IrBuilder> cachedBuilder;

    public:
        explicit LlvmBlock(llvm::BasicBlock *value);

        Ptr<IrBuilder> getBuilder();

        OptPtr<LlvmInst> findTerminatorInst() const;

        OptPtr<LlvmInst> findInstById(std::string id);
    };
}
