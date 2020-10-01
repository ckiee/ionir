#include <ionir/type_system/type_util.h>
#include <ionir/passes/semantic/entry_point_check_pass.h>
#include <ionir/passes/type_system/type_check_pass.h>

namespace ionir {
    TypeCheckPass::TypeCheckPass(ionshared::Ptr<ionshared::PassContext> context) :
        Pass(std::move(context)) {
        //
    }

    void TypeCheckPass::initialize(ionshared::PassInfo &info) {
        // TODO: Technically, we don't NEED to check for an entry point during type-check.
//        info.addRequirement<EntryPointCheckPass>();
    }

    void TypeCheckPass::visitFunction(ionshared::Ptr<Function> node) {
        ionshared::OptPtr<FunctionBody> functionBody = node->body;

        IONIR_PASS_INTERNAL_ASSERT(ionshared::util::hasValue(functionBody))

        ionshared::OptPtr<BasicBlock> entryBasicBlock = functionBody->get()->findEntryBasicBlock();

        if (!ionshared::util::hasValue(entryBasicBlock)) {
            this->context->diagnosticBuilder
                ->bootstrap(diagnostic::functionMissingEntryBasicBlock)
                ->finish();

            return;
        }

        TypeKind parentFunctionPrototypeReturnTypeKind = functionBody
            ->get()
            ->getUnboxedParent()
            ->prototype
            ->returnType
            ->typeKind;

        /**
         * Entry basic blocks must contain at least a single terminal
         * instruction if the parent function does not return void. If
         * it returns void and there is no terminal instruction, the
         * LLVM codegen pass will implicitly append a return instruction
         * with no value.
         */
        if (parentFunctionPrototypeReturnTypeKind != TypeKind::Void) {
            std::vector<ionshared::Ptr<Inst>> insts = entryBasicBlock->get()->insts;

            // TODO: CRITICAL! There may be more than a single terminal statement on basic blocks? Technically speaking LLVM does not allow that to EXECUTE, however, it can OCCUR.
            ionshared::OptPtr<Inst> terminalInst = entryBasicBlock->get()->findTerminalInst();

            if (insts.empty() || !ionshared::util::hasValue(terminalInst)) {
                this->context->diagnosticBuilder
                    ->bootstrap(diagnostic::functionReturnValueMissing)
                    ->finish();
            }
        }
    }

    void TypeCheckPass::visitReturnInst(ionshared::Ptr<ReturnInst> node) {
        ionshared::Ptr<Construct> possibleFunctionParent =
            node->getUnboxedParent()->getUnboxedParent()->getUnboxedParent();

        IONIR_PASS_INTERNAL_ASSERT(
            possibleFunctionParent->constructKind == ConstructKind::Function
        )

        ionshared::Ptr<Function> function = possibleFunctionParent->dynamicCast<Function>();
        ionshared::Ptr<Type> functionReturnType = function->prototype->returnType;
        ionshared::OptPtr<Construct> returnStatementValue = node->value;
        bool returnStatementValueSet = ionshared::util::hasValue(returnStatementValue);

        /**
         * Functions whose prototype's return type is non-void must provide
         * a value to the return instruction.
         */
        if ((functionReturnType->typeKind != TypeKind::Void) && !returnStatementValueSet) {
            this->context->diagnosticBuilder
                ->bootstrap(diagnostic::functionReturnValueMissing)

                // TODO: Fill in format.
                ->formatMessage("pending")

                ->finish();

            // TODO: Can it be made optional/continue?
            return;
        }
        else if (returnStatementValueSet) {
            switch (returnStatementValue->get()->constructKind) {
                /**
                 * Return instruction's value is a construct derived from Value<>.
                 * Compare its type to the function's return type.
                 */
                case ConstructKind::Value: {
                    /**
                     * At this point, the function returns a non-void value. Abstract its
                     * return value's type construct.
                     */
                    ionshared::Ptr<Type> returnInstValueType =
                        returnStatementValue->get()->staticCast<Value<>>()->type;

                    /**
                     * Function's return type and the return instruction's value's type
                     * do not match. Issue a type error. Even if it's returning compatible
                     * types (such as different bit length integer values) no implicit conversions
                     * are made by the compiler (everything on the IR language must be explicit).
                     */
                    if (!type_util::isSameType(returnInstValueType, functionReturnType)) {
                        this->context->diagnosticBuilder
                            ->bootstrap(diagnostic::functionReturnValueTypeMismatch)

                            // TODO: Format-in return types.
                            ->formatMessage(function->prototype->name, "pending", "pending")

                            ->finish();
                    }

                    break;
                }

                /**
                 * Return instruction's value is set, but it's a reference. The reference
                 * must be resolved then compared.
                 */
                case ConstructKind::Ref: {
                    // TODO
                    throw std::runtime_error("Not implemented");

                    break;
                }

                // TODO: What about call instruction? Limit return value to Ref<Value>.

                default: {
                    throw std::runtime_error("Unrecognized return instruction value");
                }
            }
        }
    }

    void TypeCheckPass::visitStoreInst(ionshared::Ptr<StoreInst> node) {
        TypeKind storeInstValueTypeKind = node->value->type->typeKind;
        ionshared::Ptr<AllocaInst> targetValue = node->target;

        // Attempting to store a value with a different type than what was allocated.
        if (storeInstValueTypeKind != targetValue->type->typeKind) {
            this->context->diagnosticBuilder
                ->bootstrap(diagnostic::instStoreTypeMismatch)

                // TODO: Get names for types to display on the error message.
                ->formatMessage("pending", "pending")

                ->setSourceLocation(node->sourceLocation)
                ->finish();
        }
    }
}
