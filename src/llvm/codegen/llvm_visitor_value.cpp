#include <llvm/ADT/APInt.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constant.h>
#include <ionir/construct/value/value.h>
#include <ionir/llvm/codegen/llvm_visitor.h>

namespace ionir {
    void LlvmVisitor::visitIntegerValue(Ptr<IntegerValue> node) {
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
        switch (node->getIntKind()) {
            case IntegerKind::Int1: {
                type = llvm::Type::getInt1Ty(*this->context);

                break;
            }

            case IntegerKind::Int32: {
                type = llvm::Type::getInt32Ty(*this->context);

                break;
            }

            case IntegerKind::Int64: {
                type = llvm::Type::getInt64Ty(*this->context);

                break;
            }

            case IntegerKind::Int128: {
                type = llvm::Type::getInt128Ty(*this->context);

                break;
            }

            default: {
                throw std::runtime_error("An unrecognized integer kind was provided");
            }
        }

        // At this point, type must be defined.
        if (!type.has_value()) {
            throw std::runtime_error("Expected type to be defined");
        }

        // Finally, create the LLVM value constant.
        llvm::Constant *value =
            llvm::ConstantInt::get(*type, apInt);

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
