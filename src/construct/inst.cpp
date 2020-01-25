#include <ionir/construct/section.h>
#include <ionir/passes/pass.h>

namespace ionir {
    Inst::Inst(Ptr<Section> parent, InstKind kind)
        : ChildConstruct(parent, ConstructKind::Instruction), kind(kind) {
        //
    }

    InstKind Inst::getInstKind() {
        return this->kind;
    }

    bool Inst::isTerminal() const {
        return this->kind == InstKind::Return
            || this->kind == InstKind::Branch;
    }
}
