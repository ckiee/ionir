#include <ionir/construct/function.h>
#include <ionir/passes/pass.h>
#include <ionir/const/const.h>

namespace ionir {
    Block::Block(Ptr<Function> parent, PtrSymbolTable<Section> symbolTable)
        : ChildConstruct(parent, ConstructKind::Block), ScopeAnchor<Section>(symbolTable) {
        //
    }

    void Block::accept(Pass &visitor) {
        visitor.visitBlock(this->cast<Block>());
    }

    Ast Block::getChildNodes() const {
        // TODO: De-referencing symbol table, so it's copying and it won't link back? Review.
        return Construct::convertChildren(*this->getSymbolTable());
    }

    bool Block::verify() const {
        return this->getSymbolTable()->contains(Const::sectionEntryId);
    }

    OptPtr<Section> Block::getEntrySection() {
        return this->getSymbolTable()->lookup(Const::sectionEntryId);
    }
}
