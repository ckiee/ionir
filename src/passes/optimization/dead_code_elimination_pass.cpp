#include <ionir/passes/optimization/dead_code_elimination_pass.h>

namespace ionir {
    void DeadCodeEliminationPass::visitSection(Ptr<Section> node) {
        Pass::visitSection(node);
        
        std::vector<Ptr<Inst>> insts = node->getInsts();
        bool erase = false;

        for (auto iterator = insts.begin(); iterator < insts.end(); ++iterator) {
            Ptr<Inst> inst = *iterator;

            /**
             * If applicable, erase all further instructions,
             * as they are considered dead code.
             */
            if (erase) {
                insts.erase(iterator);

                continue;
            }
            /**
             * Determine whether the current instruction
             * is of kind return and it is not the last
             * item in the vector.
             */
            else if (inst->getInstKind() == InstKind::Return && ++iterator == insts.end()) {
                /**
                 * If so, erase all following instructions,
                 * as they are considered dead code at this
                 * point.
                 */
                erase = true;
            }
        }
    }
}
