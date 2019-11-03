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
    ValueResolver(llvm::Module *module, Constants *constants)
    {
        this->module = module;
        this->constants = constants;
    }

    std::optional<llvm::Constant *> tryResolveInt(IntegerKind kind, long value, bool isSigned = true)
    {
        std::optional<LlvmIntTypeResolver> resolver = this->constants->tryGetIntTypeResolver(kind);

        if (!resolver.has_value())
        {
            return std::nullopt;
        }

        llvm::APInt apInt = llvm::APInt(value, isSigned);

        return llvm::ConstantInt::get(resolver(this->context), apInt);
    }
};
} // namespace ionir
