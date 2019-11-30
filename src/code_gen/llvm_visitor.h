#pragma once

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
#include "passes/pass.h"

namespace ionir
{
class LlvmVisitor : public Pass
{
protected:
	llvm::LLVMContext *context;

	llvm::Module *module;

	std::stack<llvm::Value *> valueStack;

	std::stack<llvm::Type *> typeStack;

	llvm::Function *function;

	std::optional<llvm::IRBuilder<>> builder;

	std::map<std::string, llvm::Value *> namedValues;

	/**
	 * Ensures that the builder is instantiated, otherwise
	 * throws a runtime error.
	 */
	void requireBuilder();

public:
	LlvmVisitor(llvm::Module *module);

	llvm::Module *getModule() const;

	std::stack<llvm::Value *> getValueStack() const;

	std::stack<llvm::Type *> getTypeStack() const;

	Node *visitFunction(Function *node) override;

	Node *visitExtern(Extern *node) override;

	Node *visitSection(Section *node) override;

	Node *visitBlock(Block *node) override;

	Node *visitType(Type *node) override;

	Node *visitBinaryExpr(BinaryExpr *node) override;

	Node *visitPrototype(Prototype *node) override;

	Node *visitInteger(IntValue *node) override;

	Node *visitChar(CharValue *node) override;

	Node *visitString(StringValue *node) override;

	Node *visitAllocaInst(AllocaInst *node) override;

	Node *visitReturnInst(ReturnInst *node) override;

	Node *visitBranchInst(BranchInst *node) override;

	Node *visitGlobalVar(GlobalVar *node) override;
};
} // namespace ionir
