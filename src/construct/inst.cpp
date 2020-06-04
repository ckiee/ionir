#include <ionir/construct/basic_block.h>
#include <ionir/passes/pass.h>

namespace ionir {
    Inst::Inst(Ptr<BasicBlock> parent, InstKind kind, OptPtr<Inst> yields)
        : ChildConstruct(parent, ConstructKind::Inst), kind(kind), yields(yields) {
        //
    }

    InstKind Inst::getInstKind() const noexcept {
        return this->kind;
    }

    OptPtr<Inst> Inst::getYields() const noexcept {
        return std::nullopt;
    }

    bool Inst::isTerminal() const noexcept {
        return this->kind == InstKind::Return
            || this->kind == InstKind::Branch;
    }
}
