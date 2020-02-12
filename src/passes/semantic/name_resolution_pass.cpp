#include <ionir/passes/semantic/name_resolution_pass.h>

namespace ionir {
    NameResolutionPass::NameResolutionPass(Ptr<StackTrace> stackTrace) : stackTrace(stackTrace), scopeStack() {
        //
    }

    void NameResolutionPass::visitModule(Ptr<Module> node) {
        Pass::visitModule(node);
        this->scopeStack.push(node->getSymbolTable());
    }

    void NameResolutionPass::visitRef(PtrRef<> node) {
        Pass::visitRef(node);

        // Node is already resolved, no need to continue.
        if (node->isResolved()) {
            return;
        }

        Ptr<Construct> owner = node->getOwner();
        std::string id = node->getId();

        switch (owner->getConstructKind()) {
            case ConstructKind::Inst: {
                Ptr<Inst> inst = owner->dynamicCast<Inst>();
                PtrSymbolTable<Inst> sectionSymbolTable = inst->getParent()->getSymbolTable();

                // The section's symbol table contains the referenced entity.
                if (sectionSymbolTable->contains(id)) {
                    node->resolve((*sectionSymbolTable)[id]);

                    std::cout << "Reference found and resolved" << std::endl;

                    return;
                }
                // TODO: Check globals.

                std::cout << "Does not contain" << std::endl;

                // Otherwise, report an undefined reference error.
                // TODO: Create NoticeContext using some sort of factory, for now throw error.
                throw std::runtime_error("Undefined reference to '" + id + "'");

                break;
            }
        }
    }

    void NameResolutionPass::visitScopeAnchor(Ptr<ScopeAnchor<>> node) {
        Pass::visitScopeAnchor(node);

        // TODO: ScopeStack should be pushed & popped, but its never popped.
        // TODO: CRITICAL: Throwing SEGFAULT because node is NULL (casting fails).
//        this->scopeStack.push(node->getSymbolTable());
    }

    Ptr<StackTrace> NameResolutionPass::getStackTrace() const {
        return this->stackTrace;
    }

    const ScopeStack &NameResolutionPass::getScopeStack() const {
        return this->scopeStack;
    }
}
