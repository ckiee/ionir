#pragma once

#include <optional>
#include <stack>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/BasicBlock.h"
#include "constructs/values/integer.h"
#include "constructs/values/char.h"
#include "constructs/values/string.h"
#include "constructs/expr/binary_expr.h"
#include "constructs/insts/inst.h"
#include "constructs/insts/branch.h"
#include "constructs/insts/alloca.h"
#include "constructs/insts/return.h"
#include "constructs/construct.h"
#include "constructs/construct_kind.h"
#include "constructs/function.h"
#include "constructs/type.h"
#include "constructs/block.h"
#include "constructs/extern.h"
#include "constructs/prototype.h"
#include "constructs/global.h"
#include "misc/stack.h"
#include "misc/helpers.h"
#include "passes/pass.h"

namespace ionir
{
class LlvmVisitor : public Pass
{
protected:
	llvm::LLVMContext *context;

	llvm::Module *module;

	Stack<llvm::Value *> valueStack;

	Stack<llvm::Type *> typeStack;

	std::optional<llvm::Function *> function;

	std::optional<llvm::IRBuilder<>> builder;

	std::map<std::string, llvm::Value *> namedValues;

	Stack<llvm::IRBuilder<>> builderTracker;

	/**
	 * Ensures that the builder is instantiated, otherwise
	 * throws a runtime error.
	 */
	void requireBuilder();

	void requireFunction();

	void setBuilder(llvm::BasicBlock *block);

	bool saveBuilder();

	bool restoreBuilder();

public:
	LlvmVisitor(llvm::Module *module);

	llvm::Module *getModule() const;

	Stack<llvm::Value *> getValueStack() const;

	Stack<llvm::Type *> getTypeStack() const;

	void visitFunction(Ptr<Function> node) override;

	void visitExtern(Ptr<Extern> node) override;

	void visitSection(Ptr<Section> node) override;

	void visitBlock(Ptr<Block> node) override;

	void visitType(Ptr<Type> node) override;

	void visitPrototype(Ptr<Prototype> node) override;

	void visitBinaryExpr(Ptr<BinaryExpr> node) override;

	void visitIntegerValue(Ptr<IntegerValue> node) override;

	void visitCharValue(Ptr<CharValue> node) override;

	void visitStringValue(Ptr<StringValue> node) override;

	void visitBooleanValue(Ptr<BooleanValue> node) override;

	void visitAllocaInst(Ptr<AllocaInst> node) override;

	void visitReturnInst(Ptr<ReturnInst> node) override;

	void visitBranchInst(Ptr<BranchInst> node) override;

	void visitGlobal(Ptr<Global> node) override;
};
} // namespace ionir
