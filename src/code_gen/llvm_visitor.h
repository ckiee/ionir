#pragma once

#include <memory>
#include <optional>
#include <stack>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_constructs/values/integer.h"
#include "ast_constructs/values/char.h"
#include "ast_constructs/values/string.h"
#include "ast_constructs/type.h"
#include "ast_constructs/block.h"
#include "ast_constructs/binary_expr.h"
#include "ast_constructs/function.h"
#include "ast_constructs/extern.h"
#include "ast_constructs/prototype.h"
#include "ast_constructs/global_var.h"
#include "ast_constructs/inst.h"
#include "ast_constructs/insts/branch.h"
#include "ast_constructs/insts/alloca.h"
#include "ast_constructs/insts/return.h"
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

	/**
	 * Ensures that the builder is instantiated, otherwise
	 * throws a runtime error.
	 */
	void requireBuilder();

	void requireFunction();

public:
	LlvmVisitor(llvm::Module *module);

	~LlvmVisitor();

	llvm::Module *getModule() const;

	Stack<llvm::Value *> getValueStack() const;

	Stack<llvm::Type *> getTypeStack() const;

	Ptr<Construct> visitFunction(Ptr<Function> node) override;

	Ptr<Construct> visitExtern(Ptr<Extern> node) override;

	Ptr<Construct> visitSection(Ptr<Section> node) override;

	Ptr<Construct> visitBlock(Ptr<Block> node) override;

	Ptr<Construct> visitType(Ptr<Type> node) override;

	Ptr<Construct> visitBinaryExpr(Ptr<BinaryExpr> node) override;

	Ptr<Construct> visitPrototype(Ptr<Prototype> node) override;

	Ptr<Construct> visitIntegerValue(Ptr<IntegerValue> node) override;

	Ptr<Construct> visitCharValue(Ptr<CharValue> node) override;

	Ptr<Construct> visitStringValue(Ptr<StringValue> node) override;

	Ptr<Construct> visitAllocaInst(Ptr<AllocaInst> node) override;

	Ptr<Construct> visitReturnInst(Ptr<ReturnInst> node) override;

	Ptr<Construct> visitBranchInst(Ptr<BranchInst> node) override;

	Ptr<Construct> visitGlobalVar(Ptr<GlobalVar> node) override;
};
} // namespace ionir
