#include <ionir/construct/function.h>
#include <ionir/passes/pass.h>
#include <ionir/const/const.h>

namespace ionir {
    Block::Block(Ptr<Function> parent, PtrSymbolTable<Section> symbolTable)
        : ChildConstruct(parent, ConstructKind::Block), ScopeAnchor<Section>(symbolTable) {
        //
    }

    void Block::accept(Pass &visitor) {
        // TODO: CRITICAL: Cast error.
//        visitor.visitScopeAnchor(this->staticCast<ScopeAnchor<Section>>());
        visitor.visitBlock(this->staticCast<Block>());
    }

    Ast Block::getChildNodes() const {
        // TODO: De-referencing symbol table, so it's copying and it won't link back? Review.
        return Construct::convertChildren(*this->getSymbolTable());
    }

    bool Block::verify() {
        return this->hasEntrySection();
    }

    OptPtr<Section> Block::getEntrySection() {
        return this->getSymbolTable()->lookup(Const::sectionEntryId);
    }

    bool Block::hasEntrySection() {
        return Util::hasValue(this->getEntrySection());
    }

    void Block::insertSection(Ptr<Section> section) {
        // TODO: Check if section exists first?
        (*this->getSymbolTable())[section->getId()] = section;
    }
}
