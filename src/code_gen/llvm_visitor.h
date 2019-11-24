#pragma once

#include <optional>
#include <stack>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/values/char.h"
#include "ast_nodes/type.h"
#include "ast_nodes/block.h"
#include "ast_nodes/binary_expr.h"
#include "ast_nodes/function.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/inst.h"

namespace ionir
{
class LlvmVisitor
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

	Node *visit(Node *node);

	Node *visitFunction(Function *node);

	Node *visitExtern(Extern *node);

	Node *visitBlock(Block *node);

	Node *visitType(Type *node);

	Node *visitBinaryExpr(BinaryExpr *node);

	Node *visitPrototype(Prototype *node);

	Node *visitInteger(LiteralInt *node);

	Node *visitInstruction(Inst *node);

	Node *visitChar(LiteralChar *node);
};
} // namespace ionir
