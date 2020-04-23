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

        // TODO: CRITICAL: Recently solved the problem which was that it was using the section's own symbol table instead of the function's to find the section (Dummy mistake). Verify that this is actually how it should be.

        switch (owner->getConstructKind()) {
            case ConstructKind::Inst: {
                Ptr<Inst> inst = owner->dynamicCast<Inst>();
                PtrSymbolTable<Section> functionSymbolTable = inst->getParent()->getParent()->getSymbolTable();

                // The function's symbol table contains the referenced entity.
                if (functionSymbolTable->contains(id)) {
                    node->resolve((*functionSymbolTable)[id]);

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
