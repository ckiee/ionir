#pragma once

#include <optional>
#include "llvm/IR/LLVMContext.h"
#include "ast_nodes/integer.h"
#include "misc/constants.h"

namespace ionir
{
class ValueResolver
{
protected:
    llvm::Module *module;

    Constants *constants;

public:
    ValueResolver(llvm::Module *module, Constants *constants);

    std::optional<llvm::Constant *> tryResolveInt(IntegerKind kind, long value, bool isSigned = true);
};
} // namespace ionir
