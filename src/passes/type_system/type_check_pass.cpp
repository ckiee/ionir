#include <ionir/passes/type_system/type_check_pass.h>

namespace ionir {
    void TypeCheckPass::visitFunction(Ptr<Function> node) {
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
                Ptr<ReturnInst> returnInst = inst->cast<ReturnInst>();

                /**
                 * Functions whose prototype's return type is non-void must provide
                 * a value to the return instruction.
                 */
                if (!returnInst->getValue().has_value()) {
                    throw std::runtime_error(
                        "Function whose prototype's return type is not void must return a corresponding value"
                    );
                }
            }
        }
    }

    void TypeCheckPass::visitStoreInst(Ptr<StoreInst> node) {
        // TODO
    }
}
