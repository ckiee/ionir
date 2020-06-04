#include <ionir/passes/semantic/name_resolution_pass.h>

namespace ionir {
    NameResolutionPass::NameResolutionPass(Ptr<StackTrace> stackTrace) : stackTrace(stackTrace), scope() {
        //
    }

    void NameResolutionPass::visitModule(Ptr<Module> node) {
        Pass::visitModule(node);

        // TODO: Is it push_back() or push_front()?
        this->scope.push_back(node->getSymbolTable());
    }

    void NameResolutionPass::visitRef(PtrRef<> node) {
        Pass::visitRef(node);

        // Node is already resolved, no need to continue.
        if (node->isResolved()) {
            return;
        }

        Ptr<Construct> owner = node->getOwner();
        std::string id = node->getId();

        // TODO: CRITICAL: Recently solved the problem which was that it was using the basic block's own symbol table instead of the function's to find the basic block (Dummy mistake). Verify that this is actually how it should be.

        switch (owner->getConstructKind()) {
            case ConstructKind::Inst: {
                Ptr<Inst> inst = owner->dynamicCast<Inst>();
                Ptr<BasicBlock> basicBlock = inst->getParent();
                PtrSymbolTable<BasicBlock> functionSymbolTable = basicBlock->getParent()->getSymbolTable();
                PtrSymbolTable<Inst> basicBlockSymbolTable = basicBlock->getSymbolTable();

                /**
                 * Check on the section's symbol table. It should take precedence
                 * before the function's symbol table.
                 */
                if (basicBlockSymbolTable->contains(id)) {
                    node->resolve(basicBlockSymbolTable->lookup(id));

                    return;
                }
                // Check on the function's symbol table for the referenced entity.
                else if (functionSymbolTable->contains(id)) {
                    node->resolve(functionSymbolTable->lookup(id));

                    return;
                }
                // TODO: Check globals, externs & modules.

                // Otherwise, report an undefined reference error.
                // TODO: Create NoticeContext using some sort of factory, for now throw error.
                throw std::runtime_error("Undefined reference to '" + id + "'");
            }

            // TODO: Finish implementation.
            default: {
                throw std::runtime_error("Unhandled construct kind");
            }
        }
    }

    void NameResolutionPass::visitScopeAnchor(Ptr<ScopeAnchor<>> node) {
        Pass::visitScopeAnchor(node);

        // TODO: ScopeStack should be pushed & popped, but its never popped.
        // TODO: CRITICAL: Throwing SEGFAULT because node is NULL (casting fails).
//        this->scopeStack.add(node->getSymbolTable());
    }

    Ptr<StackTrace> NameResolutionPass::getStackTrace() const {
        return this->stackTrace;
    }

    const std::list<PtrSymbolTable<Construct>> &NameResolutionPass::getScope() const {
        return this->scope;
    }
}
