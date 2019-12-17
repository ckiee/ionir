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
#include "ast_nodes/values/integer.h"
#include "ast_nodes/values/char.h"
#include "ast_nodes/values/string.h"
#include "ast_nodes/type.h"
#include "ast_nodes/block.h"
#include "ast_nodes/binary_expr.h"
#include "ast_nodes/function.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/global_var.h"
#include "ast_nodes/inst.h"
#include "ast_nodes/insts/branch.h"
#include "ast_nodes/insts/alloca.h"
#include "ast_nodes/insts/return.h"
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

	Ptr<Node> visitFunction(Ptr<Function> node) override;

	Ptr<Node> visitExtern(Ptr<Extern> node) override;

	Ptr<Node> visitSection(Ptr<Section> node) override;

	Ptr<Node> visitBlock(Ptr<Block> node) override;

	Ptr<Node> visitType(Ptr<Type> node) override;

	Ptr<Node> visitBinaryExpr(Ptr<BinaryExpr> node) override;

	Ptr<Node> visitPrototype(Ptr<Prototype> node) override;

	Ptr<Node> visitIntValue(Ptr<IntValue> node) override;

	Ptr<Node> visitCharValue(Ptr<CharValue> node) override;

	Ptr<Node> visitStringValue(Ptr<StringValue> node) override;

	Ptr<Node> visitAllocaInst(Ptr<AllocaInst> node) override;

	Ptr<Node> visitReturnInst(Ptr<ReturnInst> node) override;

	Ptr<Node> visitBranchInst(Ptr<BranchInst> node) override;

	Ptr<Node> visitGlobalVar(Ptr<GlobalVar> node) override;
};
} // namespace ionir
