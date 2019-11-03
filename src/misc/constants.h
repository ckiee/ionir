#pragma once

#include <map>
#include <optional>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "ast_nodes/integer.h"

namespace ionir
{
typedef llvm::IntegerType *(llvm::IntegerType::*LlvmIntTypeResolver)(llvm::LLVMContext &context);

class Constants
{
protected:
    llvm::Module *module;

    Map<IntegerKind, LlvmIntTypeResolver> integerTypeResolverMap;

public:
    Constants(llvm::Module *module)
    {
        this->module = module;

        // Register integer kind -> integer type resolvers.
        auto map = this->integerTypeResolverMap.unwrap();

        map.insert(IntegerKind::Int1, &llvm::IntegerType::getInt1Ty);
        map.insert(IntegerKind::Int32, &llvm::IntegerType::getInt32Ty);
        map.insert(IntegerKind::Int64, &llvm::IntegerType::getInt64Ty);
        map.insert(IntegerKind::Int128, &llvm::IntegerType::getInt128Ty);
    }

    std::optional<LlvmIntTypeResolver> tryGetIntTypeResolver(IntegerKind kind)
    {
        return this->integerTypeResolverMap.tryGet(kind);
    }
};
} // namespace ionir
