#pragma once

#include <stack>
#include "llvm/IR/Module.h"
#include "Construct.h"
#include "Constructs/Type.h"
#include "Constructs/Block.h"
#include "Constructs/BinaryExpr.h"
#include "Generation/ConstructType.h"

class LlvmVisitor
{
private:
    llvm::LLVMContext &context;

    llvm::Module &module;

    std::stack<llvm::Value> valueStack;

    std::stack<llvm::Type> typeStack;

    llvm::Function &function;

protected:
    llvm::Module &getModule()
    {
        return this->module;
    }

public:
    LlvmVisitor(llvm::Module module) : module(module), context(module.getContext()), function(nullptr)
    {
        //
    }

    Construct visit(Construct construct)
    {
        return construct.accept(this);
    }

    Construct visitBlock(Block *node)
    {
        // Function buffer must not be null.
        if (&this->function == nullptr)
        {
            throw "Expected the function buffer to be set, but was null";
        }

        // Create the basic block and at the same time register it under the buffer function.
        llvm::BasicBlock *block = llvm::BasicBlock::Create(this->context, (*node).getIdentifier(), &this->function);

        // TODO: Complete implementation

        return *node;
    }

    Construct visitType(Type *node)
    {
        // TODO: Hard-coded double type.
        llvm::Type *type = llvm::Type::getDoubleTy(this->context);

        bool isPointer = (*node).getIsPointer();

        // Convert type to a pointer.
        if (isPointer)
        {
            // TODO: Convert type to pointer.
        }

        this->typeStack.push(*type);

        return *node;
    }

    Construct visitBinaryExpr(BinaryExpr *node)
    {
        // Visit sides.
        this->visit((*node).getLeftSide());
        this->visit((*node).getRightSide());

        // Pop and retrieve right side.
        this->valueStack.pop();

        llvm::Value &rightSide = this->valueStack.top();

        // Pop and retrieve left side.
        this->valueStack.pop();

        llvm::Value &leftSide = this->valueStack.top();

        // TODO: Finish implementation.

        return *node;
    }

    Construct visitPrototype(Prototype *node)
    {
        // TODO: Finish implementation.

        return *node;
    }
};
