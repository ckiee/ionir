#include <exception>
#include "llvm_visitor.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constant.h"
#include "ast_nodes/inst_kind.h"
#include "ast_nodes/value.h"

namespace ionir
{
llvm::Module *LlvmVisitor::getModule() const
{
    return this->module;
}

std::stack<llvm::Value *> LlvmVisitor::getValueStack() const
{
    return this->valueStack;
}

std::stack<llvm::Type *> LlvmVisitor::getTypeStack() const
{
    return this->typeStack;
}

void LlvmVisitor::requireBuilder()
{
    // Builder must be instantiated.
    if (!this->builder.has_value())
    {
        // Otherwise, throw a runtime error.
        throw std::runtime_error("Expected builder to be instantiated");
    }
}

LlvmVisitor::LlvmVisitor(llvm::Module *module) : module(module), context(&module->getContext()), function(nullptr)
{
    this->valueStack = {};
    this->typeStack = {};
    this->namedValues = {};
}

Node *LlvmVisitor::visit(Node *node)
{
    return node->accept(this);
}

Node *LlvmVisitor::visitFunction(Function *node)
{
    if (node->getBody() == nullptr)
    {
        throw std::runtime_error("Unexpected function body to be null");
    }
    else if (node->getPrototype() == nullptr)
    {
        throw std::runtime_error("Unexpected function prototype to be null");
    }
    else if (this->module->getFunction(node->getPrototype()->getIdentifier()) != nullptr)
    {
        throw std::runtime_error("A function with the same identifier has been already previously defined");
    }

    // Clear named values.
    this->namedValues.clear();

    // Visit the prototype.
    this->visitPrototype(node->getPrototype());

    // Pop the resulting function off the stack.
    this->valueStack.pop();

    llvm::Function *function = (llvm::Function *)this->valueStack.top();

    // Set the function buffer.
    this->function = function;

    // Visit the body.
    this->visitBlock(node->getBody());

    // TODO: Verify the function.

    // Pop off the body to clean the stack.
    this->valueStack.pop();

    this->valueStack.push(function);

    return node;
}

Node *LlvmVisitor::visitExtern(Extern *node)
{
    if (node->getPrototype() == nullptr)
    {
        throw std::runtime_error("Unexpected external definition's prototype to be null");
    }
    else if (this->module->getFunction(node->getPrototype()->getIdentifier()) != nullptr)
    {
        throw std::runtime_error("Re-definition of extern not allowed");
    }

    // Visit the prototype.
    this->visitPrototype(node->getPrototype());

    // No need to push the resulting function onto the stack.
    return node;
}

Node *LlvmVisitor::visitBlock(Block *node)
{
    // Function buffer must not be null.
    if (this->function == nullptr)
    {
        throw std::runtime_error("Expected the function buffer to be set, but was null");
    }

    // Create the basic block and at the same time register it under the buffer function.
    llvm::BasicBlock *block = llvm::BasicBlock::Create(*this->context, node->getIdentifier(), this->function);

    // Create and assign the block to the builder.
    this->builder.emplace(llvm::IRBuilder<>(block));

    // Visit and append instructions.
    std::vector<Inst *> insts = node->getInsts();

    // Process instructions.
    for (const auto node : insts)
    {
        // Visit the instruction.
        this->visit(node);

        // Clean the stack off the result.
        this->valueStack.pop();
    }

    this->valueStack.push(block);

    return node;
}

Node *LlvmVisitor::visitType(Type *node)
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

    return node;
}

Node *LlvmVisitor::visitBinaryExpr(BinaryExpr *node)
{
    // Ensure builder is instantiated.
    this->requireBuilder();

    // Visit sides.
    this->visit(node->getLeftSide());

    std::optional<llvm::Value *> rightSide;

    if (node->getRightSide().has_value())
    {
        this->visit(*node->getRightSide());

        // Pop and retrieve right side.
        this->valueStack.pop();

        rightSide = this->valueStack.top();
    }

    // Pop and retrieve left side.
    this->valueStack.pop();

    llvm::Value *leftSide = this->valueStack.top();

    // TODO: Hard-coded add instruction.
    // Create the binary expression LLVM value.
    llvm::Value *binaryExpr = this->builder->CreateAdd(leftSide, *rightSide);

    this->valueStack.push(binaryExpr);

    return node;
}

Node *LlvmVisitor::visitPrototype(Prototype *node)
{
    // Retrieve argument count from the argument vector.
    uint32_t argumentCount = node->getArguments().getItems().size();

    // Create the argument buffer vector.
    std::vector<llvm::Type *> arguments = {};

    // Attempt to retrieve an existing function.
    llvm::Function *function = this->module->getFunction(node->getIdentifier());

    // A function with a matching identifier already exists.
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
    // Otherwise, function will be created.
    else
    {
        for (int i = 0; i < argumentCount; ++i)
        {
            // TODO: Wrong type.
            arguments.push_back(llvm::Type::getDoubleTy(*this->context));
        }

        // TODO: Support for infinite arguments and hard-coded return type.
        // Create the function type.
        llvm::FunctionType *type = llvm::FunctionType::get(llvm::Type::getVoidTy(*this->context), arguments, node->getArguments().getIsInfinite());

        // Cast the value to a function, since we know getCallee() will return a function.
        function = (llvm::Function *)this->module->getOrInsertFunction(node->getIdentifier(), type).getCallee();

        // Set the function's linkage.
        function->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
    }

    // Begin processing arguments. Argument count must be the same.
    if (argumentCount != function->arg_size())
    {
        throw std::runtime_error("Expected argument count to be the same as the function's argument count");
    }

    int i = 0;

    for (auto &arg : function->args())
    {
        // Retrieve the name element from the argument tuple.
        std::string name = node->getArguments().getItems()[i].second;

        // Name the argument.
        arg.setName(name);

        // Increment the counter to prepare for next iteration.
        i++;
    }

    this->valueStack.push(function);

    return node;
}

Node *LlvmVisitor::visitInteger(LiteralInt *node)
{
    // Create the APInt to provide. Acts sort of an LLVM integer value wrapper. Default to being signed to allow for a larger range of values.
    llvm::APInt apInt = llvm::APInt(node->getValue(), true);

    // TODO: Process correct int. type based on IntegerKind.
    std::optional<llvm::IntegerType *> type;

    // Create the corresponding LLVM integer type based off the node's integer kind.
    switch (node->getIntKind())
    {
    case IntegerKind::Int1:
    {
        type = llvm::Type::getInt1Ty(*this->context);

        break;
    }

    case IntegerKind::Int32:
    {
        type = llvm::Type::getInt32Ty(*this->context);

        break;
    }

    case IntegerKind::Int64:
    {
        type = llvm::Type::getInt64Ty(*this->context);

        break;
    }

    case IntegerKind::Int128:
    {
        type = llvm::Type::getInt128Ty(*this->context);

        break;
    }

    default:
    {
        throw std::runtime_error("An unrecognized integer kind was provided");
    }
    }

    // At this point, type must be defined.
    if (!type.has_value())
    {
        throw std::runtime_error("Expected type to be defined");
    }

    // Finally, create the LLVM value constant.
    llvm::Constant *value = llvm::ConstantInt::get(*type, apInt);

    // Push the value onto the value stack.
    this->valueStack.push(value);

    return node;
}

Node *LlvmVisitor::visitChar(LiteralChar *node)
{
    // TODO

    return node;
}

Node *LlvmVisitor::visitString(StringValue *node)
{
    // Create the global string pointer.
    llvm::Constant *value = this->builder->CreateGlobalStringPtr(node->getValue());

    // Push the value onto the value stack.
    this->valueStack.push(value);

    return node;
}

Node *LlvmVisitor::visitAllocaInst(AllocaInst *node)
{
    this->visit(node->getType());

    llvm::Type *type = this->typeStack.top();

    this->typeStack.pop();

    // Create the LLVM equivalent alloca instruction using the buffered builder.
    llvm::AllocaInst *allocaInst = this->builder->CreateAlloca(type, (llvm::Value *)nullptr, node->getIdentifier());

    this->valueStack.push(allocaInst);

    return node;
}

Node *LlvmVisitor::visitReturnInst(ReturnInst *node)
{
    this->visit(node->getValue());

    llvm::Value *value = this->valueStack.top();

    this->valueStack.pop();

    // Create the LLVM equivalent return instruction using the buffered builder.
    llvm::ReturnInst *returnInst = this->builder->CreateRet(value);

    this->valueStack.push(returnInst);

    return node;
}

// TODO: Re-write.
Node *LlvmVisitor::visitInst(Inst *node)
{
    this->requireBuilder();

    switch (node->getInstKind())
    {
    case InstKind::Alloca:
    {
        this->visitAllocaInst((AllocaInst *)node);
    }

    case InstKind::Return:
    {
        this->visitReturnInst((ReturnInst *)node);
    }

    default:
    {
        throw std::runtime_error("Unrecognized instruction kind");
    }
    }

    return node;
}

Node *LlvmVisitor::visitIfStmt(IfStmt *node)
{
    // Visit condition.
    this->visit(node->getCondition());

    llvm::Value *condition = this->valueStack.top();

    this->valueStack.pop();

    // Visit body.
    this->visit(node->getBody());

    llvm::BasicBlock *body = (llvm::BasicBlock *)this->valueStack.top();

    this->valueStack.pop();

    // Prepare otherwise block with a default value.
    llvm::BasicBlock *otherwise = nullptr;

    // Visit otherwise block if applicable.
    if (node->getOtherwise().has_value())
    {
        this->visit(*node->getOtherwise());
        otherwise = (llvm::BasicBlock *)this->valueStack.top();
        this->valueStack.pop();
    }

    // Create the LLVM branch instruction.
    this->builder->CreateCondBr(condition, body, otherwise);

    return node;
}

Node *LlvmVisitor::visitGlobalVar(GlobalVar *node)
{
    this->visit(node->getType());

    llvm::Type *type = this->typeStack.top();

    this->typeStack.pop();

    llvm::GlobalVariable *globalVar = (llvm::GlobalVariable *)this->module->getOrInsertGlobal(node->getIdentifier(), type);

    // Assign value if applicable.
    if (node->getValue().has_value())
    {
        // Visit global variable value.
        this->visit(*node->getValue());

        llvm::Value *value = this->valueStack.top();

        this->valueStack.pop();

        // TODO: Value needs to be verified to be llvm::Constant?

        globalVar->setInitializer((llvm::Constant *)value);
    }

    return node;
}
} // namespace ionir
