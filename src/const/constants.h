#pragma once

#include <string>
#include <map>
#include <optional>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "construct/values/integer.h"
#include "syntax/token_type.h"
#include "misc/map.h"

namespace ionir
{
typedef llvm::IntegerType *(llvm::IntegerType::*LlvmIntTypeResolver)(llvm::LLVMContext &context);

class Const
{
protected:
    static Map<IntegerKind, LlvmIntTypeResolver> integerTypeResolverMap;

public:
    static const std::string sectionInternalPrefix;

    static const std::string sectionEntryId;

    static std::optional<LlvmIntTypeResolver> tryGetIntTypeResolver(IntegerKind kind);

    static std::map<TokenType, int> operatorPrecedence;
};
} // namespace ionir
