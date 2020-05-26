#include <string>
#include <ionir/construct/basic_block.h>
#include <ionir/passes/semantic/name_shadowing_pass.h>

namespace ionir {
    void NameShadowingPass::visitInst(Ptr<Inst> node) {
        Pass::visitInst(node);

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
                if (function->getLocalVariables()->contains(name)) {
                    throw std::runtime_error(
                        "SemanticError: Function parameter being shadowed by local variable '" + name + "'"
                    );
                }
            }
        }
    }
}
