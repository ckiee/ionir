#include <exception>
#include "llvm/ADT/APInt.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constant.h"
#include "construct/values/value.h"
#include "misc/util.h"
#include "llvm_visitor.h"

namespace ionir
{
llvm::Module *LlvmVisitor::getModule() const
{
    return this->module;
}

Stack<llvm::Value *> LlvmVisitor::getValueStack() const
{
    return this->valueStack;
}

Stack<llvm::Type *> LlvmVisitor::getTypeStack() const
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

void LlvmVisitor::requireFunction()
{
    if (this->function == nullptr)
    {
        throw std::runtime_error("Expected the function buffer to be set, but was null");
    }
}

void LlvmVisitor::setBuilder(llvm::BasicBlock *block)
{
    this->builder.emplace(llvm::IRBuilder<>(block));
}

bool LlvmVisitor::saveBuilder()
{
    if (!this->builder.has_value())
    {
        return false;
    }

    this->builderTracker.push(*this->builder);

    return true;
}

bool LlvmVisitor::restoreBuilder()
{
    if (this->builderTracker.isEmpty())
    {
        return false;
    }

    this->builder.emplace(this->builderTracker.pop());

    return true;
}

LlvmVisitor::LlvmVisitor(llvm::Module *module)
    : module(module), context(&module->getContext()), function(std::nullopt), valueStack(), typeStack(), builderTracker(), namedValues({})
{
    //
}

void LlvmVisitor::visitFunction(Ptr<Function> node)
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
    llvm::Function *function = (llvm::Function *)this->valueStack.pop();

    // Set the function buffer.
    this->function = function;

    // Visit the function's body.
    this->visitBlock(node->getBody());

    // TODO: Verify the resulting LLVM function (through LLVM).

    // Push the function back onto the stack.
    this->valueStack.push(function);
}

void LlvmVisitor::visitExtern(Ptr<Extern> node)
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
}

void LlvmVisitor::visitSection(Ptr<Section> node)
{
    // Function buffer must not be null.
    this->requireFunction();

    // Create the basic block and at the same time register it under the buffer function.
    llvm::BasicBlock *block = llvm::BasicBlock::Create(*this->context, node->getId(), *this->function);

    // Create and assign the block to the builder.
    this->setBuilder(block);

    // Visit and append instructions.
    std::vector<Ptr<Inst>> insts = node->getInsts();

    // Process instructions.
    for (const auto inst : insts)
    {
        // Visit the instruction.
        this->visitInst(inst);

        // Clean the stack off the result.
        this->valueStack.pop();
    }

    this->valueStack.push(block);
}

void LlvmVisitor::visitBlock(Ptr<Block> node)
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
    std::optional<Ptr<Section>> entry = node->getEntrySection();

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
}

void LlvmVisitor::visitType(Ptr<Type> node)
{
    // TODO: Hard-coded double type.
    llvm::Type *type = llvm::Type::getDoubleTy(*this->context);

    // Convert type to a pointer if applicable.
    if (node->getIsPointer())
    {
        // TODO: Convert type to pointer.
    }

    this->typeStack.push(type);
}

void LlvmVisitor::visitBinaryExpr(Ptr<BinaryExpr> node)
{
    // Ensure builder is instantiated.
    this->requireBuilder();

    // Visit sides.
    this->visitExpr(node->getLeftSide());

    std::optional<llvm::Value *> rightSide = std::nullopt;

    // Process right side if applicable.
    if (node->getRightSide().has_value())
    {
        this->visitExpr(*node->getRightSide());

        // Retrieve and pop right side.
        rightSide = this->valueStack.pop();
    }

    // Retrieve left side before popping.
    llvm::Value *leftSide = this->valueStack.pop();

    // TODO: Hard-coded add instruction.
    // Create the binary expression LLVM value.
    llvm::Value *binaryExpr =
        this->builder->CreateAdd(leftSide, *rightSide);

    this->valueStack.push(binaryExpr);
}

void LlvmVisitor::visitPrototype(Ptr<Prototype> node)
{
    // Retrieve argument count from the argument vector.
    uint32_t argumentCount = node->getArgs()->getItems().size();

    // Create the argument buffer vector.
    std::vector<llvm::Type *> arguments = {};

    // Attempt to retrieve an existing function.
    llvm::Function *function(
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
        llvm::FunctionType *type =
            llvm::FunctionType::get(llvm::Type::getVoidTy(*this->context), arguments, node->getArgs()->getIsInfinite());

        // Cast the value to a function, since we know getCallee() will return a function.
        function =
            (llvm::Function *)this->module->getOrInsertFunction(node->getId(), type).getCallee();

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
}

void LlvmVisitor::visitIntegerValue(Ptr<IntegerValue> node)
{
    /**
     * Create the APInt to provide. Acts sort of an
     * LLVM integer value wrapper. Default to being
     * signed to allow for a larger range of values.
     */
    llvm::APInt apInt = llvm::APInt(node->getValue(), true);

    // TODO: Process correct int. type based on IntegerKind.
    std::optional<llvm::IntegerType *> type = std::nullopt;

    /**
     * Create the corresponding LLVM integer type
     * based off the node's integer kind.
     */
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
    llvm::Constant *value =
        llvm::ConstantInt::get(*type, apInt);

    // Push the value onto the value stack.
    this->valueStack.push(value);
}

void LlvmVisitor::visitCharValue(Ptr<CharValue> node)
{
    // TODO
}

void LlvmVisitor::visitStringValue(Ptr<StringValue> node)
{
    this->requireBuilder();

    // Create the global string pointer.
    llvm::Constant *value =
        this->builder->CreateGlobalStringPtr(node->getValue());

    // Push the value onto the value stack.
    this->valueStack.push(value);
}

void LlvmVisitor::visitBooleanValue(Ptr<BooleanValue> node)
{
    // Create the boolean type along with the LLVM value.
    llvm::IntegerType *type = llvm::Type::getInt1Ty(*this->context);
    llvm::Constant *value = llvm::ConstantInt::get(type, llvm::APInt(1, node->getValue(), false));

    // Push the resulting boolean constant onto the stack.
    this->valueStack.push(value);
}

void LlvmVisitor::visitAllocaInst(Ptr<AllocaInst> node)
{
    this->visitType(node->getType());

    llvm::Type *type = this->typeStack.pop();

    /**
     * Create the LLVM equivalent alloca instruction
     * using the buffered builder.
     */
    llvm::AllocaInst *allocaInst =
        this->builder->CreateAlloca(type, (llvm::Value *)nullptr, node->getId());

    this->valueStack.push(allocaInst);
}

void LlvmVisitor::visitReturnInst(Ptr<ReturnInst> node)
{
    std::optional<Ptr<Value>> value = node->getValue();
    llvm::ReturnInst *returnInst = this->builder->CreateRetVoid();

    if (value.has_value())
    {
        this->visitValue(*value);

        llvm::Value *value = this->valueStack.pop();

        /**
         * Create the LLVM equivalent return instruction
         * using the buffered builder.
         */
        llvm::ReturnInst *returnInst =
            this->builder->CreateRet(value);
    }

    this->valueStack.push(returnInst);
}

void LlvmVisitor::visitBranchInst(Ptr<BranchInst> node)
{
    /**
     * Relocate all instructions following the
     * branch instruction onto a new stage of
     * the parent.
     */
    // TODO
    // node->getParent()->relocateInsts(node->getParent()->getParent());

    // Visit condition.
    this->visitExpr(node->getCondition());

    llvm::Value *condition = this->valueStack.pop();

    this->saveBuilder();

    // Visit body.
    this->visitSection(node->getBody());

    llvm::BasicBlock *body =
        (llvm::BasicBlock *)this->valueStack.pop();

    // Prepare otherwise block with a default value.
    std::optional<llvm::BasicBlock *> otherwise = std::nullopt;

    // Visit otherwise block if applicable.
    if (node->getOtherwise().has_value())
    {
        this->visitSection(*node->getOtherwise());
        otherwise = (llvm::BasicBlock *)this->valueStack.pop();
    }

    this->restoreBuilder();

    // Create the LLVM branch instruction.
    llvm::BranchInst *branchInst =
        this->builder->CreateCondBr(condition, body, otherwise.value_or(nullptr));

    this->valueStack.push(branchInst);
}

void LlvmVisitor::visitGlobal(Ptr<Global> node)
{
    this->visitType(node->getType());

    llvm::Type *type = this->typeStack.pop();

    llvm::GlobalVariable *globalVar =
        (llvm::GlobalVariable *)this->module->getOrInsertGlobal(node->getId(), type);

    // Assign value if applicable.
    if (node->getValue().has_value())
    {
        // Visit global variable value.
        this->visitValue(*node->getValue());

        llvm::Value *value = this->valueStack.pop();

        // TODO: Value needs to be created from below commented statement.
        // llvm::Constant* initializerValue = llvm::Constant::getIntegerValue(llvm::Type);

        // TODO: You can't just cast llvm::value to constant! See above.
        globalVar->setInitializer((llvm::Constant *)value);
    }
}
} // namespace ionir
