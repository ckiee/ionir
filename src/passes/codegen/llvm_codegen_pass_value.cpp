#include <llvm/ADT/APInt.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constant.h>
#include <ionir/construct/value.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visitIntegerLiteral(ionshared::Ptr<IntegerLiteral> node) {
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

        ionshared::Ptr<Type> nodeType = node->getType();

        if (nodeType->getTypeKind() != TypeKind::Integer) {
            throw std::runtime_error("Integer value's type must be integer type");
        }

        this->visitIntegerType(nodeType->dynamicCast<IntegerType>());

        llvm::Type *type = this->typeStack.pop();

        // Finally, create the LLVM value constant.
        llvm::Constant *value = llvm::ConstantInt::get(type, apInt);

        this->valueStack.push(value);
//        this->addToScope(node, value);
    }

    void LlvmCodegenPass::visitCharLiteral(ionshared::Ptr<CharLiteral> node) {
        this->requireContext();
        this->requireBuilder();

        llvm::Type *charType = llvm::Type::getInt8Ty(**this->buffers.llvmContext);
        llvm::Constant *value = llvm::ConstantInt::get(charType, node->getValue());

        this->valueStack.push(value);
//        this->addToScope(node, value);
    }

    void LlvmCodegenPass::visitStringLiteral(ionshared::Ptr<StringLiteral> node) {
        this->requireBuilder();

        // Create the global string pointer.
        llvm::Constant *value = this->getLlvmBuilder()->CreateGlobalStringPtr(node->getValue());

        this->valueStack.push(value);
//        this->addToScope(node, value);
    }

    void LlvmCodegenPass::visitBooleanLiteral(ionshared::Ptr<BooleanLiteral> node) {
        this->requireContext();

        // Create the boolean type along with the LLVM value.
        llvm::IntegerType *type = llvm::Type::getInt1Ty(**this->buffers.llvmContext);
        llvm::Constant *value = llvm::ConstantInt::get(type, llvm::APInt(1, node->getValue(), false));

        this->valueStack.push(value);
//        this->addToScope(node, value);
    }
}
