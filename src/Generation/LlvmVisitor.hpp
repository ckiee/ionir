#pragma once

#include <stack>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "Generation/Construct.hpp"
#include "Constructs/Type.hpp"
#include "Constructs/Block.hpp"
#include "Constructs/BinaryExpr.hpp"
#include "Constructs/Function.hpp"
#include "Constructs/Extern.hpp"
#include "Generation/ConstructType.hpp"
#include "Constructs/Prototype.hpp"

class LlvmVisitor
{
private:
	llvm::LLVMContext *context;

	llvm::Module *module;

	std::stack<llvm::Value *> valueStack;

	std::stack<llvm::Type *> typeStack;

	llvm::Function *function;

	llvm::IRBuilder<> *builder;

	std::map<std::string, llvm::Value> namedValues;

protected:
	llvm::Module *getModule()
	{
		return this->module;
	}

public:
	LlvmVisitor(llvm::Module *module) : module(module), context(&module->getContext()), function(nullptr), builder(nullptr)
	{
		this->valueStack = {};
		this->typeStack = {};
		this->namedValues = {};
	}

	Construct visit(Construct *node)
	{
		return node->accept(this);
	}

	Construct visitFunction(Function *node)
	{
		if (&node->getBody() == nullptr)
		{
			throw "Unexpected function body to be null";
		}
		else if (&node->getPrototype() == nullptr)
		{
			throw "Unexpected function prototype to be null";
		}
		else if (this->module->getFunction(node->getPrototype().getIdentifier()) != nullptr)
		{
			throw "A function with the same identifier has been already previously defined";
		}

		// Clear named values.
		this->namedValues.clear();

		// Visit the prototype.
		this->visitPrototype(&node->getPrototype());

		// Pop the resulting function off the stack.
		this->valueStack.pop();

		llvm::Function *function = (llvm::Function *)this->valueStack.top();

		// Set the function buffer.
		this->function = function;

		// Visit the body.
		this->visitBlock(&node->getBody());

		// TODO: Verify the function.

		// Pop off the body to clean the stack.
		this->valueStack.pop();

		this->valueStack.push(function);

		return *node;
	}

	Construct visitExtern(Extern *node)
	{
		if (&node->getPrototype() == nullptr)
		{
			throw std::runtime_error("Unexpected external definition's prototype to be null");
		}
		else if (this->module->getFunction(node->getPrototype().getIdentifier()) != nullptr)
		{
			throw std::runtime_error("Re-definition of extern not allowed");
		}

		// Visit the prototype.
		this->visitPrototype(&node->getPrototype());

		// No need to push the resulting function onto the stack.
		return *node;
	}

	Construct visitBlock(Block *node)
	{
		// Function buffer must not be null.
		if (&this->function == nullptr)
		{
			throw std::runtime_error("Expected the function buffer to be set, but was null");
		}

		// Create the basic block and at the same time register it under the buffer function.
		llvm::BasicBlock *block = llvm::BasicBlock::Create(*this->context, node->getIdentifier(), this->function);

		// Create and assign the builder.
		this->builder = &llvm::IRBuilder<>(*this->context);

		// Visit and append instructions.
		std::vector<Construct> insts = node->getInsts();

		// Process instructions.
		for (std::vector<Construct>::iterator iterator = insts.begin(); iterator != insts.end(); iterator++)
		{
			// Visit the instruction.
			this->visit(&*iterator);

			// Clean the stack off the result.
			this->valueStack.pop();
		}

		this->valueStack.push(block);

		return *node;
	}

	Construct visitType(Type *node)
	{
		// TODO: Hard-coded double type.
		llvm::Type *type = llvm::Type::getDoubleTy(*this->context);

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
		this->visit(&node->getLeftSide());
		this->visit(&node->getRightSide());

		// Pop and retrieve right side.
		this->valueStack.pop();

		llvm::Value *rightSide = this->valueStack.top();

		// Pop and retrieve left side.
		this->valueStack.pop();

		llvm::Value *leftSide = this->valueStack.top();

		// Create the binary expression LLVM value.
		llvm::Value *binaryExpr = this->builder->CreateAdd(leftSide, rightSide);

		this->valueStack.push(binaryExpr);

		return *node;
	}

	Construct visitPrototype(Prototype *node)
	{
		// Retrieve argument count from the argument vector.
		uint32_t argumentCount = node->getArguments().size();

		// Create the argument buffer vector.
		std::vector<llvm::Type *> arguments = {};

		// Attempt to retrieve an existing function.
		llvm::Function *function = this->module->getFunction(node->getIdentifier());

		if (function != nullptr)
		{
			// Function already has a body, disallow re-definition.
			if (function->getBasicBlockList().size() > 0)
			{
				throw std::runtime_error("Cannot re-define function");
			}
			// If the function takes a different number of arguments, reject.
			else if (function->arg_size() != argumentCount)
			{
				throw std::runtime_error("Re-definition of function with a different amount arguments");
			}
		}
		else
		{
			for (int i = 0; i < argumentCount; ++i)
			{
				// TODO: Wrong type.
				arguments.push_back(llvm::Type::getDoubleTy(*this->context));
			}

			// TODO: Support for infinite arguments and hard-coded return type.
			// Create the function type.
			llvm::FunctionType *type = llvm::FunctionType::get(llvm::Type::getVoidTy(*this->context), arguments, node->getHasInfiniteArguments());

			function = this->module->functions.getOrInsertFunction(node->getIdentifier(), type);

			// Set the function's linkage.
			function->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
		}

		// Process arguments.
		for (int i = 0; i < argumentCount; ++i)
		{
			// Retrieve the name element from the argument tuple.
			std::string name = node->getArguments()[i].second;

			// Retrieve the argument at the current index iterator.
			llvm::Value *argument = function->args[i];

			// Name the argument.
			argument->setName(name);
		}

		this->valueStack.push(function);

		return *node;
	}
};
