#include <llvm/ADT/APInt.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constant.h>
#include <ionir/construct/value.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visitIntegerValue(Ptr<IntegerValue> node) {
        /**
         * Create the APInt (Arbitrary-precision integer)
         * to provide. Acts sort of an LLVM integer value
         * wrapper.
         */
        llvm::APInt apInt = llvm::APInt(
            (unsigned)node->getType()->getIntegerKind(),
            node->getValue(),
            node->getType()->getIsSigned()
        );

        Ptr<Type> nodeType = node->getType();

        if (nodeType->getTypeKind() != TypeKind::Integer) {
            throw std::runtime_error("Integer value's type must be integer type");
        }

        this->visitIntegerType(nodeType->dynamicCast<IntegerType>());

        llvm::Type *type = this->typeStack.pop();

        // Finally, create the LLVM value constant.
        llvm::Constant *value = llvm::ConstantInt::get(type, apInt);

        this->emittedEntities.front()[node] = value;

        // Push the value onto the value stack.
        this->valueStack.push(value);
    }

    void LlvmCodegenPass::visitCharValue(Ptr<CharValue> node) {
        this->requireBuilder();

        llvm::Type *charType = llvm::Type::getInt8Ty(*this->context);
        llvm::Constant *value = llvm::ConstantInt::get(charType, node->getValue());

        this->emittedEntities.front()[node] = value;
        this->valueStack.push(value);
    }

    void LlvmCodegenPass::visitStringValue(Ptr<StringValue> node) {
        this->requireBuilder();

        // Create the global string pointer.
        llvm::Constant *value = this->builder->CreateGlobalStringPtr(node->getValue());

        this->emittedEntities.front()[node] = value;
        // Push the value onto the value stack.
        this->valueStack.push(value);
    }

    void LlvmCodegenPass::visitBooleanValue(Ptr<BooleanValue> node) {
        // Create the boolean type along with the LLVM value.
        llvm::IntegerType *type = llvm::Type::getInt1Ty(*this->context);
        llvm::Constant *value = llvm::ConstantInt::get(type, llvm::APInt(1, node->getValue(), false));

        this->emittedEntities.front()[node] = value;

        // Push the resulting boolean constant onto the stack.
        this->valueStack.push(value);
    }
}
