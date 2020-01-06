#include <llvm/ADT/APInt.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constant.h>
#include <ionir/construct/value.h>
#include <ionir/llvm/codegen/llvm_visitor.h>

namespace ionir {
    void LlvmVisitor::visitIntegerValue(Ptr<IntegerValue> node) {
        /**
         * Create the APInt to provide. Acts sort of an
         * LLVM integer value wrapper. Default to being
         * signed to allow for a larger range of values.
         */
        llvm::APInt apInt = llvm::APInt(node->getValue(), true);

        Ptr<Type> nodeType = node->getType();

        if (nodeType->getTypeKind() != TypeKind::Integer) {
            throw std::runtime_error("Integer value's type must be integer type");
        }

        this->visitIntegerType(nodeType->cast<IntegerType>());

        llvm::Type *type = this->typeStack.pop();

        // Finally, create the LLVM value constant.
        llvm::Constant *value =
            llvm::ConstantInt::get(type, apInt);

        // Push the value onto the value stack.
        this->valueStack.push(value);
    }

    void LlvmVisitor::visitCharValue(Ptr<CharValue> node) {
        // TODO
    }

    void LlvmVisitor::visitStringValue(Ptr<StringValue> node) {
        this->requireBuilder();

        // Create the global string pointer.
        llvm::Constant *value =
            this->builder->CreateGlobalStringPtr(node->getValue());

        // Push the value onto the value stack.
        this->valueStack.push(value);
    }

    void LlvmVisitor::visitBooleanValue(Ptr<BooleanValue> node) {
        // Create the boolean type along with the LLVM value.
        llvm::IntegerType *type = llvm::Type::getInt1Ty(*this->context);
        llvm::Constant *value = llvm::ConstantInt::get(type, llvm::APInt(1, node->getValue(), false));

        // Push the resulting boolean constant onto the stack.
        this->valueStack.push(value);
    }
}
