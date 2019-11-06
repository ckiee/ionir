#pragma once

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

	llvm::IRBuilder<> *builder;

	std::map<std::string, llvm::Value> namedValues;

	llvm::Module *getModule() const;

public:
	LlvmVisitor(llvm::Module *module);

	Node *visit(Node *node);

	Node *visitFunction(Function *node);

	Node *visitExtern(Extern *node);

	Node *visitBlock(Block *node);

	Node *visitType(Type *node);

	Node *visitBinaryExpr(BinaryExpr *node);

	Node *visitPrototype(Prototype *node);

	Node *visitInteger(LiteralInteger *node);
};
} // namespace ionir
