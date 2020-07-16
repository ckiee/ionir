#pragma once

#include <optional>
#include <llvm/IR/BasicBlock.h>
#include <ionshared/misc/helpers.h>
#include <ionir/misc/wrapper.h>
#include <ionir/misc/safe_wrapper.h>
#include <ionir/misc/helpers.h>
#include "ir_builder.h"
#include "llvm_inst.h"

namespace ionir {
    class LlvmBlock : public SafeWrapper<llvm::BasicBlock *> {
    private:
        ionshared::OptPtr<IrBuilder> cachedBuilder;

    public:
        explicit LlvmBlock(llvm::BasicBlock *value);

        ionshared::Ptr<IrBuilder> getBuilder();

        ionshared::OptPtr<LlvmInst> findTerminatorInst() const;

        ionshared::OptPtr<LlvmInst> findInstById(std::string id);
    };
}
