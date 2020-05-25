#include <ionir/construct/section.h>
#include <ionir/passes/pass.h>

namespace ionir {
    Inst::Inst(Ptr<Section> parent, InstKind kind)
        : ChildConstruct(parent, ConstructKind::Inst), kind(kind) {
        //
    }

    InstKind Inst::getInstKind() noexcept {
        return this->kind;
    }

    bool Inst::isTerminal() const noexcept {
        return this->kind == InstKind::Return
            || this->kind == InstKind::Branch;
    }
}
