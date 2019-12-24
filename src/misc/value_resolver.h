#pragma once

#include <optional>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Constant.h>
#include "construct/values/integer.h"

namespace ionir {
    class ValueResolver {
    protected:
        llvm::Module *module;

    public:
        ValueResolver(llvm::Module *module);

        std::optional<llvm::Constant *> tryResolveInt(IntegerKind kind, long value, bool isSigned = true);
    };
}
