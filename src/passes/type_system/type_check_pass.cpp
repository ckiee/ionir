#include <ionir/passes/type_system/type_check_pass.h>

namespace ionir {
    void TypeCheckPass::visitFunction(ionshared::Ptr<Function> node) {
        Pass::visitFunction(node);

        ionshared::OptPtr<BasicBlock> entryBasicBlock = node->getBody()->findEntryBasicBlock();

        if (!Util::hasValue(entryBasicBlock)) {
            throw std::runtime_error("Entry basic block for function body is not set");
        }

        std::vector<ionshared::Ptr<Inst>> insts = entryBasicBlock->get()->getInsts();
        ionshared::OptPtr<Inst> terminalInst = entryBasicBlock->get()->findTerminalInst();

        // All basic blocks must contain at least a terminal instruction.
        if (insts.empty() || !Util::hasValue(terminalInst)) {
            throw std::runtime_error("Section must contain at least a terminal instruction");
        }

        for (const auto inst : insts) {
            if (inst->getInstKind() == InstKind::Return) {
                ionshared::Ptr<ReturnInst> returnInst = inst->staticCast<ReturnInst>();
                TypeKind returnTypeKind = node->getPrototype()->getReturnType()->getTypeKind();
                ionshared::OptPtr<Construct> returnInstValue = returnInst->getValue();
                bool returnInstValueSet = Util::hasValue(returnInstValue);

                /**
                 * Functions whose prototype's return type is non-void must provide
                 * a value to the return instruction.
                 */
                if (returnTypeKind != TypeKind::Void && !returnInstValueSet) {
                    throw std::runtime_error(
                        "Function whose prototype's return type is not void must return a corresponding value"
                    );
                }
                /**
                 * Return instruction's value construct is a literal value. Process
                 * it simply by comparing its type.
                 */
                else if (returnInstValueSet && (*returnInstValue)->getConstructKind() == ConstructKind::Value) {
                    // TODO: Broke when removed expr. Must fix.
                    throw std::runtime_error("Not implemented / broken");
//                    /**
//                     * At this point, the function returns a non-void value. Abstract its
//                     * return value's type construct.
//                     */
//                    ionshared::Ptr<Type> returnInstValueType = (*returnInstValue)->staticCast<Value>()->getType();
//
//                    /**
//                     * Function's return type and the return instruction's value's type
//                     * do not match. Issue a type error.
//                     */
//                    if (returnInstValueType->getTypeKind() != returnTypeKind) {
//                        throw std::runtime_error(
//                            "Function prototype's return value's type and return instruction's value's type do not match"
//                        );
//                    }
                }
                /**
                 * Return instruction's value is set, but it's a reference. The reference
                 * must be resolved then compared.
                 */
                else if (returnInstValueSet) {
                    // TODO
                    throw std::runtime_error("Not implemented");
                }
            }
        }
    }

    void TypeCheckPass::visitStoreInst(ionshared::Ptr<StoreInst> node) {
        Pass::visitStoreInst(node);

        // TODO: Implement.
    }
}
