#include "value_resolver.h"

namespace ionir
{
ValueResolver::ValueResolver(llvm::Module *module, Constants *constants)
{
    this->module = module;
    this->constants = constants;
}

std::optional<llvm::Constant *> ValueResolver::tryResolveInt(IntegerKind kind, long value, bool isSigned)
{
    std::optional<LlvmIntTypeResolver> resolver = this->constants->tryGetIntTypeResolver(kind);

    if (!resolver.has_value())
    {
        return std::nullopt;
    }

    llvm::APInt apInt = llvm::APInt(value, isSigned);

    // TODO
    return std::nullopt;

    //return llvm::ConstantInt::get(resolver(this->context), apInt);
}
} // namespace ionir
