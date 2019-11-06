#pragma once

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
