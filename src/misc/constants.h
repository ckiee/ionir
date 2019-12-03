#pragma once

#include <string>
#include <map>
#include <optional>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "ast_nodes/values/integer.h"
#include "syntax/token_type.h"
#include "misc/map.h"

namespace ionir
{
typedef llvm::IntegerType *(llvm::IntegerType::*LlvmIntTypeResolver)(llvm::LLVMContext &context);

class Const
{
protected:
    llvm::Module *module;

    Map<IntegerKind, LlvmIntTypeResolver> integerTypeResolverMap;

public:
    static const std::string sectionInternalPrefix;

    static const std::string sectionEntryId;

    Const(llvm::Module *module);

    std::optional<LlvmIntTypeResolver> tryGetIntTypeResolver(IntegerKind kind);

    static const std::map<TokenType, int> tokenPrecedence;
};
} // namespace ionir
