#pragma once

#include <stack>
#include "llvm/IR/Module.h"
#include "Construct.hh"
#include "Constructs/Type.hh"
#include "Generation/ConstructType.hh"

class LlvmVisitor
{
private:
    llvm::LLVMContext &context;

    llvm::Module &module;

    std::stack<llvm::Value> valueStack;

    std::stack<llvm::Type> typeStack;

protected:
    llvm::Module &getModule()
    {
        return this->module;
    }

public:
    LlvmVisitor(llvm::Module module) : module(module), context(module.getContext())
    {
        //
    }

    Construct visit(Construct construct)
    {
        return construct.accept(this);
    }

    Construct visitType(Type node)
    {
        // TODO: Hard-coded double type.
        llvm::Type *type = llvm::Type::getDoubleTy(this->context);

        bool isPointer = node.getIsPointer();

        if (isPointer)
        {
            // TODO: Convert type to pointer.
        }

        return node;
    }
};
