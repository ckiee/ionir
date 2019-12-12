#include <exception>
#include "llvm_visitor.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constant.h"
#include "ast_nodes/inst_kind.h"
#include "ast_nodes/value.h"
#include "misc/util.h"

namespace ionir
{
std::shared_ptr<llvm::Module> LlvmVisitor::getModule() const
{
    return this->module;
}

Stack<std::shared_ptr<llvm::Value>> LlvmVisitor::getValueStack() const
{
    return this->valueStack;
}

Stack<std::shared_ptr<llvm::Type>> LlvmVisitor::getTypeStack() const
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

LlvmVisitor::LlvmVisitor(std::shared_ptr<llvm::Module> module)
    : module(module), context(&module->getContext()), function(nullptr), valueStack(), typeStack()
{
    this->namedValues = {};
}

LlvmVisitor::~LlvmVisitor()
{
    this->valueStack.clear();
    this->typeStack.clear();
}

std::shared_ptr<Node> LlvmVisitor::visitFunction(std::shared_ptr<Function> node)
{
    if (!node->verify())
    {
        throw std::runtime_error("Function verification failed");
    }
    else if (this->module->getFunction(node->getPrototype()->getId()) != nullptr)
    {
        throw std::runtime_error("A function with the same identifier has been already previously defined");
    }

    // Clear named values.
    this->namedValues.clear();

    // Visit the prototype.
    this->visitPrototype(node->getPrototype());

    // Retrieve the resulting function off the stack.
    std::shared_ptr<llvm::Function> function =
        std::static_pointer_cast<llvm::Function>(this->valueStack.pop());

    // Set the function buffer.
    this->function = function;

    // Visit the function's body.
    this->visitBlock(node->getBody());

    // TODO: Verify the resulting LLVM function (through LLVM).

    // Push the function back onto the stack.
    this->valueStack.push(function);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitExtern(std::shared_ptr<Extern> node)
{
    if (node->getPrototype() == nullptr)
    {
        throw std::runtime_error("Unexpected external definition's prototype to be null");
    }
    else if (this->module->getFunction(node->getPrototype()->getId()) != nullptr)
    {
        throw std::runtime_error("Re-definition of extern not allowed");
    }

    // Visit the prototype.
    this->visitPrototype(node->getPrototype());

    // No need to push the resulting function onto the stack.
    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitSection(std::shared_ptr<Section> node)
{
    // Function buffer must not be null.
    if (this->function == nullptr)
    {
        throw std::runtime_error("Expected the function buffer to be set, but was null");
    }

    // Create the basic block and at the same time register it under the buffer function.
    std::shared_ptr<llvm::BasicBlock> block(llvm::BasicBlock::Create(*this->context, node->getId(), this->function.get()));

    // Create and assign the block to the builder.
    this->builder.emplace(llvm::IRBuilder<>(block.get()));

    // Visit and append instructions.
    std::vector<std::shared_ptr<Inst>> insts = node->getInsts();

    // Process instructions.
    for (const auto inst : insts)
    {
        // Visit the instruction.
        this->visit(inst);

        // Clean the stack off the result.
        this->valueStack.pop();
    }

    /**
     * Entry section contains no instructions, add 
     * a mandatory return void instruction at the end.
     */
    if (node->getKind() == SectionKind::Entry && node->getInsts().size() == 0)
    {
        this->requireBuilder();
        (*this->builder).CreateRetVoid();
    }

    this->valueStack.push(block);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitBlock(std::shared_ptr<Block> node)
{
    // Verify the block before continuing.
    if (!node->verify())
    {
        throw std::runtime_error("Block failed to be verified");
    }

    /**
     * Retrieve the entry section from the block.
     * At this point, it should be guaranteed to be set.
     */
    std::optional<std::shared_ptr<Section>> entry = node->getEntrySection();

    /**
     * Entry section must be set. Redundant check,
     * since the verify should function ensure that 
     * the block contains a single entry section, but
     * just to make sure.
     */
    if (!entry.has_value())
    {
        throw std::runtime_error("No entry section exists for block");
    }

    // Visit all the block's section(s).
    for (const auto section : node->getSections())
    {
        this->visitSection(section);
        this->valueStack.pop();
    }

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitType(std::shared_ptr<Type> node)
{
    // TODO: Hard-coded double type.
    std::shared_ptr<llvm::Type> type(
        llvm::Type::getDoubleTy(this->context.get()));

    // Convert type to a pointer if applicable.
    if (node->getIsPointer())
    {
        // TODO: Convert type to pointer.
    }

    this->typeStack.push(type);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitBinaryExpr(std::shared_ptr<BinaryExpr> node)
{
    // Ensure builder is instantiated.
    this->requireBuilder();

    // Visit sides.
    this->visit(node->getLeftSide());

    std::optional<std::shared_ptr<llvm::Value>> rightSide = std::nullopt;

    // Process right side if applicable.
    if (node->getRightSide().has_value())
    {
        this->visit(*node->getRightSide());

        // Retrieve and pop right side.
        rightSide = this->valueStack.pop();
    }

    // Retrieve left side before popping.
    std::shared_ptr<llvm::Value> leftSide = this->valueStack.pop();

    // TODO: Hard-coded add instruction.
    // Create the binary expression LLVM value.
    std::shared_ptr<llvm::Value> binaryExpr(
        this->builder->CreateAdd(leftSide.get(), (*rightSide).get()));

    this->valueStack.push(binaryExpr);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitPrototype(std::shared_ptr<Prototype> node)
{
    // Retrieve argument count from the argument vector.
    uint32_t argumentCount = node->getArgs()->getItems().size();

    // Create the argument buffer vector.
    std::vector<std::shared_ptr<llvm::Type>> arguments = {};

    // Attempt to retrieve an existing function.
    std::shared_ptr<llvm::Function> function(
        this->module->getFunction(node->getId()));

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
        std::shared_ptr<llvm::FunctionType> type(
            llvm::FunctionType::get(llvm::Type::getVoidTy(*this->context), arguments, node->getArgs()->getIsInfinite()));

        // Cast the value to a function, since we know getCallee() will return a function.
        function.reset(
            (llvm::Function *)this->module->getOrInsertFunction(node->getId(), type).getCallee());

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
        std::string name = node->getArgs()->getItems()[i].second;

        // Name the argument.
        arg.setName(name);

        // Increment the counter to prepare for next iteration.
        i++;
    }

    this->valueStack.push(function);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitIntValue(std::shared_ptr<IntValue> node)
{
    /**
     * Create the APInt to provide. Acts sort of an
     * LLVM integer value wrapper. Default to being
     * signed to allow for a larger range of values.
     */
    llvm::APInt apInt = llvm::APInt(node->getValue(), true);

    // TODO: Process correct int. type based on IntegerKind.
    std::optional<std::shared_ptr<llvm::IntegerType>> type = std::nullopt;

    /**
     * Create the corresponding LLVM integer type
     * based off the node's integer kind.
     */
    switch (node->getIntKind())
    {
    case IntegerKind::Int1:
    {
        type.reset(llvm::Type::getInt1Ty(*this->context));

        break;
    }

    case IntegerKind::Int32:
    {
        type.reset(llvm::Type::getInt32Ty(*this->context));

        break;
    }

    case IntegerKind::Int64:
    {
        type.reset(llvm::Type::getInt64Ty(*this->context));

        break;
    }

    case IntegerKind::Int128:
    {
        type.reset(llvm::Type::getInt128Ty(*this->context));

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
    std::shared_ptr<llvm::Constant> value(
        llvm::ConstantInt::get((*type).get(), apInt));

    // Push the value onto the value stack.
    this->valueStack.push(value);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitCharValue(std::shared_ptr<CharValue> node)
{
    // TODO

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitStringValue(std::shared_ptr<StringValue> node)
{
    // Create the global string pointer.
    std::shared_ptr<llvm::Constant> value(
        this->builder->CreateGlobalStringPtr(node->getValue()));

    // Push the value onto the value stack.
    this->valueStack.push(value);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitAllocaInst(std::shared_ptr<AllocaInst> node)
{
    this->visit(node->getType());

    std::shared_ptr<llvm::Type> type = this->typeStack.pop();

    /**
     * Create the LLVM equivalent alloca instruction
     * using the buffered builder.
     */
    std::shared_ptr<llvm::AllocaInst> allocaInst(
        this->builder->CreateAlloca(type.get(), (llvm::Value *)nullptr, node->getId()));

    this->valueStack.push(allocaInst);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitReturnInst(std::shared_ptr<ReturnInst> node)
{
    this->visit(node->getValue());

    std::shared_ptr<llvm::Value> value = this->valueStack.pop();

    /**
     * Create the LLVM equivalent return instruction
     * using the buffered builder.
     */
    std::shared_ptr<llvm::ReturnInst> returnInst(
        this->builder->CreateRet(value.get()));

    this->valueStack.push(returnInst);

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitBranchInst(std::shared_ptr<BranchInst> node)
{
    // Visit condition.
    this->visit(node->getCondition());

    std::shared_ptr<llvm::Value> condition = this->valueStack.pop();

    // Visit body.
    this->visit(node->getBody());

    std::shared_ptr<llvm::BasicBlock> body(
        std::static_pointer_cast<llvm::BasicBlock>(this->valueStack.pop()));

    // Prepare otherwise block with a default value.
    std::shared_ptr<llvm::BasicBlock> otherwise = nullptr;

    // Visit otherwise block if applicable.
    if (node->getOtherwise().has_value())
    {
        this->visit(*node->getOtherwise());
        otherwise = std::static_pointer_cast<llvm::BasicBlock *>(this->valueStack.pop());
    }

    // Create the LLVM branch instruction.
    this->builder->CreateCondBr(condition.get(), body.get(), otherwise.get());

    return node;
}

std::shared_ptr<Node> LlvmVisitor::visitGlobalVar(std::shared_ptr<GlobalVar> node)
{
    this->visitType(node->getType());

    std::shared_ptr<llvm::Type> type = this->typeStack.pop();

    std::shared_ptr<llvm::GlobalVariable> globalVar(
        (llvm::GlobalVariable *)this->module->getOrInsertGlobal(node->getId(), type.get()));

    // Assign value if applicable.
    if (node->getValue().has_value())
    {
        // Visit global variable value.
        this->visit(*node->getValue());

        std::shared_ptr<llvm::Value> value = this->valueStack.pop();

        // TODO: Value needs to be created from below commented statement.
        // llvm::Constant* initializerValue = llvm::Constant::getIntegerValue(llvm::Type);

        // TODO: You can't just cast llvm::value to constant! See above.
        globalVar->setInitializer((llvm::Constant *)value.get());
    }

    return node;
}
} // namespace ionir
