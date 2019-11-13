#include <exception>
#include "llvm_visitor.h"

namespace ionir
{
llvm::Module *LlvmVisitor::getModule() const
{
    return this->module;
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
    std::vector<Node *> insts = node->getInsts();

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
    this->visit(node->getRightSide());

    // Pop and retrieve right side.
    this->valueStack.pop();

    llvm::Value *rightSide = this->valueStack.top();

    // Pop and retrieve left side.
    this->valueStack.pop();

    llvm::Value *leftSide = this->valueStack.top();

    // Create the binary expression LLVM value.
    llvm::Value *binaryExpr = this->builder->CreateAdd(leftSide, rightSide);

    this->valueStack.push(binaryExpr);

    return node;
}

Node *LlvmVisitor::visitPrototype(Prototype *node)
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
        std::string name = node->getArguments()[i].second;

        // Name the argument.
        arg.setName(name);

        // Increment the counter to prepare for next iteration.
        i++;
    }

    this->valueStack.push(function);

    return node;
}

Node *LlvmVisitor::visitInteger(LiteralInteger *node)
{
    // Create the APInt to provide. Acts sort of an LLVM integer value wrapper. Default to being signed to allow for a larger range of values.
    llvm::APInt apInt = llvm::APInt(node->getValue(), true);

    // TODO: Process correct int. type based on IntegerKind.
    std::optional<llvm::IntegerType *> type;

    // Create the corresponding LLVM integer type based off the node's integer kind.
    switch (node->getKind())
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
} // namespace ionir
