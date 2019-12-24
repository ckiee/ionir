#include <optional>
#include "construct/section.h"
#include "construct/insts/return.h"
#include "semantic_analysis.h"

namespace ionir {
    void SemanticAnalysisPass::functionReturnCheck(Ptr<Function> node) {
        // TODO: Hard-coded id.
        if (node->getPrototype()->getReturnType()->getId() != "void") {
            std::optional<Ptr<Section>> entrySection = node->getBody()->getEntrySection();

            if (!entrySection.has_value()) {
                throw std::runtime_error("Entry section for function body is not set");
            }

            for (auto inst : (*entrySection)->getInsts()) {
                if (inst->getInstKind() == InstKind::Return) {
                    Ptr<ReturnInst> returnInst = inst->cast<ReturnInst>();

                    if (!returnInst->getValue().has_value()) {
                        throw std::runtime_error(
                                "Function whose prototype's return type is not void must return a corresponding value");
                    }
                }
            }
        }
    }

    void SemanticAnalysisPass::visitFunction(Ptr<Function> node) {
        this->functionReturnCheck(node);
    }
}
