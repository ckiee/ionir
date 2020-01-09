#include <ionir/passes/semantic/name_resolution_pass.h>

namespace ionir {
    NameResolutionPass::NameResolutionPass(Ptr<StackTrace> stackTrace) : stackTrace(stackTrace) {
        //
    }

    void NameResolutionPass::visitRef(PtrRef<> node) {
        // Node is already resolved, no need to continue.
        if (node->isResolved()) {
            return;
        }

        Ptr<Construct> owner = node->getOwner();
        std::string id = node->getId();

        switch (owner->getConstructKind()) {
            case ConstructKind::Instruction: {
                Ptr<Inst> inst = owner->cast<Inst>();
                PtrSymbolTable<Inst> sectionSymbolTable = inst->getParent()->getSymbolTable();

                // The section's symbol table contains the referenced entity.
                if (sectionSymbolTable.contains(id)) {
                    node->resolve(sectionSymbolTable[id]);

                    return;
                }
                // TODO: Check globals.

                // Otherwise, report an undefined reference error.
                // TODO: Create NoticeContext using some sort of factory, for now throw error.
                throw std::runtime_error("Undefined reference to '" + id + "'");

                break;
            }
        }
    }

    Ptr<StackTrace> NameResolutionPass::getStackTrace() const {
        return this->stackTrace;
    }
}
