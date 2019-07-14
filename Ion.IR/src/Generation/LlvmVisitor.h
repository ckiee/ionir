#pragma once

#include <stack>
#include "llvm/IR/Module.h"
#include "Construct.h"
#include "Constructs/Type.h"
#include "Constructs/Block.h"
#include "Constructs/BinaryExpr.h"
#include "Generation/ConstructType.h"
#include "Constructs/Prototype.h"

class LlvmVisitor
{
private:
    llvm::LLVMContext &context;

    llvm::Module &module;

    std::stack<llvm::Value*> valueStack;

    std::stack<llvm::Type*> typeStack;

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
        llvm::BasicBlock *block = llvm::BasicBlock::Create(this->context, node->getIdentifier(), &this->function);

        // TODO: Complete implementation

        return *node;
    }

    Construct visitType(Type *node)
    {
        // TODO: Hard-coded double type.
        llvm::Type *type = llvm::Type::getDoubleTy(this->context);

        bool isPointer = node->getIsPointer();

        // Convert type to a pointer.
        if (isPointer)
        {
            // TODO: Convert type to pointer.
        }

        this->typeStack.push(type);

        return *node;
    }

    Construct visitBinaryExpr(BinaryExpr *node)
    {
        // Visit sides.
        this->visit(node->getLeftSide());
        this->visit(node->getRightSide());

        // Pop and retrieve right side.
        this->valueStack.pop();

        llvm::Value *rightSide = this->valueStack.top();

        // Pop and retrieve left side.
        this->valueStack.pop();

        llvm::Value *leftSide = this->valueStack.top();

        // TODO: Finish implementation.

        return *node;
    }

    Construct visitPrototype(Prototype *node)
    {
		// Retrieve argument count from the argument vector.
		uint32_t argumentCount = node->getArguments().size();

		// Create the argument buffer vector.
		std::vector<llvm::Type*> arguments = {};

		// Attempt to retrieve an existing function.
		llvm::Function *function = this->module.getFunction(node->getIdentifier());

		if (function != nullptr) {
			// Function already has a body, disallow re-definition.
			if (function->getBasicBlockList().size() > 0)
			{
				throw "Cannot re-define function: {node.Identifier}";
			}
			// If the function takes a different number of arguments, reject.
			else if (function->arg_size() != argumentCount)
			{
				throw "Re-definition of function with a different amount arguments";
			}
		}
		else {
			for (int i = 0; i < argumentCount; ++i)
			{
				// TODO: Wrong type.
				arguments.push_back(llvm::Type::getDoubleTy(this->context));
			}

			// TODO: Support for infinite arguments and hard-coded return type.
			// Create the function type.
			llvm::FunctionType *type = llvm::FunctionType::get(llvm::Type::getVoidTy(this->context), arguments, node->getHasInfiniteArguments());

			function = this->module.functions.getOrInsertFunction(node->getIdentifier(), type);

			// Set the function's linkage.
			function->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
		}

		// Process arguments.
		for (int i = 0; i < argumentCount; ++i)
		{
			// Retrieve the name element from the argument tuple.
			std::string name = std::get<1>(node->getArguments()[i]);

			// Retrieve the argument at the current index iterator.
			llvm::Value *argument = function->args[i];

			// Name the argument.
			argument->setName(name);
		}

		this->valueStack.push(function);

		return *node;
    }
};
