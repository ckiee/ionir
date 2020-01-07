#include <string>
#include <ionir/construct/section.h>
#include <ionir/construct/inst/return.h>
#include <ionir/passes/semantic_analysis.h>

namespace ionir {
    SemanticAnalysisPass::SemanticAnalysisPass() {
        //
    }

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

    void SemanticAnalysisPass::visitInst(Ptr<Inst> node) {
        Ptr<Function> function = node->getParent()->getParent()->getParent();
        Ptr<Args> args = function->getPrototype()->getArgs();

        /**
         * Compare the function's parameters against
         * its local variable symbol table to ensure
         * no name shadowing occurs.
         */
        if (!args->getIsInfinite()) {
            for (const auto argEntry : args->getItems().unwrap()) {
                std::string name = argEntry.first;

                // Shadowing function parameter.
                if (function->getLocalVariables().contains(name)) {
                    throw std::runtime_error(
                        "SemanticError: Function parameter being shadowed by local variable '" + name + "'"
                    );
                }
            }
        }
    }
}
