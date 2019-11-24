#pragma once

#include <string>
#include "llvm/IR/Module.h"
#include "misc/wrapper.h"
#include "context.h"

namespace ionir
{
class Module : public Wrapper<llvm::Module *>
{
protected:
    Context *context;

public:
    Module(llvm::Module *module, Context *context);

    Module(llvm::Module *module);

    Context *getContext() const;

    std::string getAsString() const;

    void print();

    void printToLlvmErrs() const;
};
} // namespace ionir
