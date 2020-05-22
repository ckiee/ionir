#include <ionir/passes/type_system/type_check_pass.h>

namespace ionir {
    void TypeCheckPass::visitFunction(Ptr<Function> node) {
        Pass::visitFunction(node);

        OptPtr<Section> entrySection = node->getBody()->getEntrySection();

        if (!entrySection.has_value()) {
            throw std::runtime_error("Entry section for function body is not set");
        }

        std::vector<Ptr<Inst>> insts = entrySection->get()->getInsts();

        // All sections must contain at least a terminal instruction.
        if (insts.empty() || !insts[0]->isTerminal()) {
            throw std::runtime_error("Section must contain at least a terminal instruction");
        }

        for (const auto inst : insts) {
            if (inst->getInstKind() == InstKind::Return) {
                Ptr<ReturnInst> returnInst = inst->staticCast<ReturnInst>();
                TypeKind returnTypeKind = node->getPrototype()->getReturnType()->getTypeKind();
                OptPtr<Value<>> returnInstValue = returnInst->getValue();
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
                else if (returnInstValueSet) {
                    /**
                     * At this point, the function returns a non-void value. Abstract its
                     * return value's type construct.
                     */
                    Ptr<Type> returnInstValueType = returnInstValue->get()->getType();

                    /**
                     * Function's return type and the return instruction's value's type
                     * do not match. Issue a type error.
                     */
                    if (returnInstValueType->getTypeKind() != returnTypeKind) {
                        throw std::runtime_error(
                            "Function prototype's return value's type and return instruction's value's type do not match"
                        );
                    }
                }
            }
        }
    }

    void TypeCheckPass::visitStoreInst(Ptr<StoreInst> node) {
        Pass::visitStoreInst(node);

        // TODO: Implement.
    }
}
