#pragma once

#include <string>
#include <map>
#include <optional>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "ast_nodes/values/integer.h"
#include "misc/map.h"

namespace ionir
{
typedef llvm::IntegerType *(llvm::IntegerType::*LlvmIntTypeResolver)(llvm::LLVMContext &context);

class Constants
{
protected:
    llvm::Module *module;

    Map<IntegerKind, LlvmIntTypeResolver> integerTypeResolverMap;

public:
    static const std::string sectionInternalPrefix;

    static const std::string sectionEntryIdentifier;

    Constants(llvm::Module *module);

    std::optional<LlvmIntTypeResolver> tryGetIntTypeResolver(IntegerKind kind);

    std::map<TokenType, int> tokenPrecedence = {
        {TokenType::OperatorAdd, 20},
        {TokenType::OperatorSub, 20},
        {TokenType::OperatorMultiply, 40},
        {TokenType::OperatorDivide, 40},
        {TokenType::OperatorModulo, 40},
        {TokenType::OperatorExponent, 80},
    };
};
} // namespace ionir
