#include <ionir/passes/pass.h>

namespace ionir {
    Pass::Pass(ionshared::Ptr<ionshared::PassContext> context) :
        ionshared::BasePass<Construct>(std::move(context)) {
        //
    }

    void Pass::visit(ionshared::Ptr<Construct> node) {
        node->accept(*this);

        // TODO: Hotfix for circular dep.
        if (node->getConstructKind() == ConstructKind::Value) {
            this->visitValue(node->staticCast<Value<>>());

            // No need to visit children for this node.
            return;
        }

        this->visitChildren(node);
    }

    void Pass::visitChildren(ionshared::Ptr<Construct> node) {
        // TODO: Will it cause StackOverflow error with large ASTs?
        Ast children = node->getChildNodes();

        /**
         * After visiting the node, attempt to
         * visit all its children as well.
         */
        for (const auto &child : children) {
            // TODO: CRITICAL: What if 'child' (AstNode) is not boxed under Construct?
            this->visit(child);
        }
    }

    void Pass::visitFunction(ionshared::Ptr<Function> node) {
        //
    }

    void Pass::visitExtern(ionshared::Ptr<Extern> node) {
        //
    }

    void Pass::visitBasicBlock(ionshared::Ptr<BasicBlock> node) {
        //
    }

    void Pass::visitFunctionBody(ionshared::Ptr<FunctionBody> node) {
        //
    }

    void Pass::visitPrototype(ionshared::Ptr<Prototype> node) {
        //
    }

    void Pass::visitVarReference(ionshared::Ptr<VariableRef> node) {
        //
    }

    void Pass::visitValue(ionshared::Ptr<Value<>> node) {
        switch (node->getValueKind()) {
            case ValueKind::Character: {
                this->visitCharLiteral(node->dynamicCast<CharLiteral>());

                break;
            }

            case ValueKind::Integer: {
                this->visitIntegerLiteral(node->dynamicCast<IntegerLiteral>());

                break;
            }

            case ValueKind::String: {
                this->visitStringLiteral(node->dynamicCast<StringLiteral>());

                break;
            }

            case ValueKind::Boolean: {
                this->visitBooleanLiteral(node->dynamicCast<BooleanLiteral>());

                break;
            }

            default: {
                throw std::runtime_error("Unknown value kind");
            }
        }
    }

    void Pass::visitIntegerLiteral(ionshared::Ptr<IntegerLiteral> node) {
        //
    }

    void Pass::visitCharLiteral(ionshared::Ptr<CharLiteral> node) {
        //
    }

    void Pass::visitStringLiteral(ionshared::Ptr<StringLiteral> node) {
        //
    }

    void Pass::visitBooleanLiteral(ionshared::Ptr<BooleanLiteral> node) {
        //
    }

    void Pass::visitInst(ionshared::Ptr<Inst> node) {
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

            case InstKind::Jump: {
                this->visitJumpInst(node->dynamicCast<JumpInst>());

                break;
            }

            default: {
                throw std::runtime_error("Unknown instruction kind");
            }
        }
    }

    void Pass::visitAllocaInst(ionshared::Ptr<AllocaInst> node) {
        //
    }

    void Pass::visitReturnInst(ionshared::Ptr<ReturnInst> node) {
        //
    }

    void Pass::visitBranchInst(ionshared::Ptr<BranchInst> node) {
        //
    }

    void Pass::visitCallInst(ionshared::Ptr<CallInst> node) {
        //
    }

    void Pass::visitStoreInst(ionshared::Ptr<StoreInst> node) {
        //
    }

    void Pass::visitJumpInst(ionshared::Ptr<JumpInst> node) {
        //
    }

    void Pass::visitGlobal(ionshared::Ptr<Global> node) {
        //
    }

    void Pass::visitStructDecl(ionshared::Ptr<StructDecl> node) {
        //
    }

    void Pass::visitType(ionshared::Ptr<Type> node) {
        //
    }

    void Pass::visitIntegerType(ionshared::Ptr<IntegerType> node) {
        //
    }

    void Pass::visitVoidType(ionshared::Ptr<VoidType> node) {
        //
    }

    void Pass::visitBooleanType(ionshared::Ptr<BooleanType> node) {
        //
    }

    void Pass::visitPointerType(ionshared::Ptr<PointerType> node) {
        //
    }

    void Pass::visitModule(ionshared::Ptr<Module> node) {
        //
    }

    void Pass::visitDirective(Directive node) {
        //
    }

    void Pass::visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node) {
        //
    }

    void Pass::visitErrorMarker(ionshared::Ptr<ErrorMarker> node) {
        //
    }
}
