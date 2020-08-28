#include <ionir/construct/function.h>
#include <ionir/passes/pass.h>
#include <ionir/const/const.h>

namespace ionir {
    FunctionBody::FunctionBody(
        ionshared::Ptr<Function> parent,
        PtrSymbolTable<BasicBlock> symbolTable
    ) :
        ChildConstruct(std::move(parent),
        ConstructKind::FunctionBody),
        ScopeAnchor<BasicBlock>(std::move(symbolTable)) {
        //
    }

    void FunctionBody::accept(Pass &visitor) {
        // TODO: CRITICAL: Cast error.
//        visitor.visitScopeAnchor(this->staticCast<ScopeAnchor<Section>>());
        visitor.visitFunctionBody(this->staticCast<FunctionBody>());
    }

    Ast FunctionBody::getChildNodes() {
        return Construct::convertChildren(this->getSymbolTable());
    }

    bool FunctionBody::verify() {
        return this->hasEntryBasicBlock();
    }

    ionshared::OptPtr<BasicBlock> FunctionBody::findEntryBasicBlock() {
        return this->getSymbolTable()->lookup(Const::basicBlockEntryId);
    }

    bool FunctionBody::hasEntryBasicBlock() {
        return ionshared::Util::hasValue(this->findEntryBasicBlock());
    }

    void FunctionBody::insertBasicBlock(const ionshared::Ptr<BasicBlock> &basicBlock) {
        // TODO: Check if section exists first?
        (*this->getSymbolTable())[basicBlock->getId()] = basicBlock;

        // TODO: Consider making symbol table read-only so this is controlled.
        // Update the basic block's parent.
        basicBlock->setParent(this->dynamicCast<FunctionBody>());
    }
}
