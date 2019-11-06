#pragma once

namespace ionir
{
typedef llvm::IntegerType *(llvm::IntegerType::*LlvmIntTypeResolver)(llvm::LLVMContext &context);

class Constants
{
protected:
    llvm::Module *module;

    Map<IntegerKind, LlvmIntTypeResolver> integerTypeResolverMap;

public:
    Constants(llvm::Module *module);

    std::optional<LlvmIntTypeResolver> tryGetIntTypeResolver(IntegerKind kind);
};
} // namespace ionir
