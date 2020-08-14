#include <ionir/construct/basic_block.h>
#include <ionir/passes/pass.h>

namespace ionir {
    Inst::Inst(ionshared::Ptr<BasicBlock> parent, InstKind kind, ionshared::OptPtr<Inst> yields)
        : ChildConstruct(std::move(parent), ConstructKind::Inst), kind(kind), yields(std::move(yields)) {
        //
    }

    InstKind Inst::getInstKind() const noexcept {
        return this->kind;
    }

    ionshared::OptPtr<Inst> Inst::getYields() const noexcept {
        return this->yields;
    }

    bool Inst::isTerminal() const noexcept {
        return this->kind == InstKind::Return
            || this->kind == InstKind::Branch;
    }
}
