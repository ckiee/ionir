#include <ionir/passes/pass.h>

namespace ionir {
    void Pass::prepare() {
        //
    }

    void Pass::finish() {
        //
    }

    void Pass::visit(Ptr<Construct> node) {
        node->accept(*this);

        // TODO: Hotfix for circular dep.
        if (node->getConstructKind() == ConstructKind::Ref) {
            this->visitRef(node->staticCast<Ref<>>());

            // No need to visit children for this node.
            return;
        }
        else if (node->getConstructKind() == ConstructKind::Value) {
            this->visitValue(node->staticCast<Value<>>());

            // No need to visit children for this node.
            return;
        }

        this->visitChildren(node);
    }

    void Pass::visitChildren(Ptr<Construct> node) {
        // TODO: Will it cause StackOverflow error with large ASTs?
        /**
         * After visiting the node, attempt to
         * visit all its children as well.
         */
        for (const auto child : node->getChildNodes()) {
            // TODO: CRITICAL: What if 'child' (AstNode) is not boxed under Construct?
            this->visit(child->staticCast<Construct>());
        }
    }

    void Pass::visitFunction(Ptr<Function> node) {
        //
    }

    void Pass::visitExtern(Ptr<Extern> node) {
        //
    }

    void Pass::visitBasicBlock(Ptr<BasicBlock> node) {
        //
    }

    void Pass::visitFunctionBody(Ptr<FunctionBody> node) {
        //
    }

    void Pass::visitPrototype(Ptr<Prototype> node) {
        //
    }

    void Pass::visitVarReference(Ptr<VariableRef> node) {
        //
    }

    void Pass::visitValue(Ptr<Value<>> node) {
        switch (node->getValueKind()) {
            // TODO: Missing boolean value kind.

            case ValueKind::Character: {
                this->visitCharValue(node->dynamicCast<CharValue>());

                break;
            }

            case ValueKind::Integer: {
                this->visitIntegerValue(node->dynamicCast<IntegerValue>());

                break;
            }

            case ValueKind::String: {
                this->visitStringValue(node->dynamicCast<StringValue>());

                break;
            }

            case ValueKind::Boolean: {
                this->visitBooleanValue(node->dynamicCast<BooleanValue>());

                break;
            }

            default: {
                throw std::runtime_error("Unknown value kind");
            }
        }
    }

    void Pass::visitIntegerValue(Ptr<IntegerValue> node) {
        //
    }

    void Pass::visitCharValue(Ptr<CharValue> node) {
        //
    }

    void Pass::visitStringValue(Ptr<StringValue> node) {
        //
    }

    void Pass::visitBooleanValue(Ptr<BooleanValue> node) {
        //
    }

    void Pass::visitInst(Ptr<Inst> node) {
        switch (node->getInstKind()) {
            case InstKind::Alloca: {
                this->visitAllocaInst(node->dynamicCast<AllocaInst>());

                break;
            }

            case InstKind::Branch: {
                this->visitBranchInst(node->dynamicCast<BranchInst>());

                break;
            }

            // TODO: Missing break inst.

            case InstKind::Return: {
                this->visitReturnInst(node->dynamicCast<ReturnInst>());

                break;
            }

            case InstKind::Call: {
                this->visitCallInst(node->dynamicCast<CallInst>());

                break;
            }

            case InstKind::Store: {
                this->visitStoreInst(node->dynamicCast<StoreInst>());

                break;
            }

            default: {
                throw std::runtime_error("Unknown instruction kind");
            }
        }
    }

    void Pass::visitAllocaInst(Ptr<AllocaInst> node) {
        //
    }

    void Pass::visitReturnInst(Ptr<ReturnInst> node) {
        //
    }

    void Pass::visitBranchInst(Ptr<BranchInst> node) {
        //
    }

    void Pass::visitCallInst(Ptr<CallInst> node) {
        //
    }

    void Pass::visitStoreInst(Ptr<StoreInst> node) {
        //
    }

    void Pass::visitGlobal(Ptr<Global> node) {
        //
    }

    void Pass::visitStructDecl(Ptr<StructDecl> node) {
        //
    }

    void Pass::visitType(Ptr<Type> node) {
        //
    }

    void Pass::visitIntegerType(Ptr<IntegerType> node) {
        //
    }

    void Pass::visitVoidType(Ptr<VoidType> node) {
        //
    }

    void Pass::visitModule(Ptr<Module> node) {
        //
    }

    void Pass::visitDirective(Directive node) {
        //
    }

    void Pass::visitRef(PtrRef<> node) {
        //
    }

    void Pass::visitScopeAnchor(Ptr<ScopeAnchor<>> node) {
        //
    }

    void Pass::visitRegisterAssign(Ptr<ionir::RegisterAssign> node) {
        //
    }
}
