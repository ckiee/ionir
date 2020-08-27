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

    uint32_t Inst::getOrder() {
        std::optional<uint32_t> order =
            this->getParent()->locate(this->dynamicCast<Inst>());

        if (!order.has_value()) {
            throw std::runtime_error("Could not locate instruction in parent");
        }

        return *order;
    }
}
