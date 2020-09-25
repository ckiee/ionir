#include <ionir/construct/basic_block.h>
#include <ionir/passes/pass.h>

namespace ionir {
    Inst::Inst(ionshared::Ptr<BasicBlock> parent, InstKind kind) :
        ChildConstruct(std::move(parent), ConstructKind::Inst),
        instKind(kind) {
        //
    }

    InstKind Inst::getInstKind() const noexcept {
        return this->instKind;
    }

    bool Inst::isTerminal() const noexcept {
        return this->instKind == InstKind::Return
            || this->instKind == InstKind::Branch;
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
