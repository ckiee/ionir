#include <ionir/construct/function.h>
#include <ionir/passes/pass.h>
#include <ionir/const/const.h>

namespace ionir {
    FunctionBody::FunctionBody(Ptr<Function> parent, PtrSymbolTable<BasicBlock> symbolTable)
        : ChildConstruct(parent, ConstructKind::Block), ScopeAnchor<BasicBlock>(symbolTable) {
        //
    }

    void FunctionBody::accept(Pass &visitor) {
        // TODO: CRITICAL: Cast error.
//        visitor.visitScopeAnchor(this->staticCast<ScopeAnchor<Section>>());
        visitor.visitFunctionBody(this->staticCast<FunctionBody>());
    }

    Ast FunctionBody::getChildNodes() const {
        // TODO: De-referencing symbol table, so it's copying and it won't link back? Review.
        return Construct::convertChildren(*this->getSymbolTable());
    }

    bool FunctionBody::verify() {
        return this->hasEntryBasicBlock();
    }

    OptPtr<BasicBlock> FunctionBody::findEntryBasicBlock() {
        return this->getSymbolTable()->lookup(Const::basicBlockEntryId);
    }

    bool FunctionBody::hasEntryBasicBlock() {
        return Util::hasValue(this->findEntryBasicBlock());
    }

    void FunctionBody::insertBasicBlock(Ptr<BasicBlock> basicBlock) {
        // TODO: Check if section exists first?
        (*this->getSymbolTable())[basicBlock->getId()] = basicBlock;
    }
}
