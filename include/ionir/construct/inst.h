#pragma once

#include <ionir/construct/value.h>
#include <ionir/construct/pseudo/child_construct.h>

namespace ionir {
    class Pass;

    class BasicBlock;

    struct InstOpts {
        const ionshared::Ptr<BasicBlock> parent;
    };

    enum class InstKind {
        Alloca,

        Store,

        Call,

        Return,

        Break,

        Branch,

        PtrToInt,

        Zext,

        Trunc,

        Icmp,

        Jump
    };

    struct Inst : ConstructWithParent<BasicBlock> {
        const InstKind instKind;

        Inst(ionshared::Ptr<BasicBlock> parent, InstKind kind);

        void accept(Pass &visitor) override = 0;

        [[nodiscard]] InstKind getInstKind() const noexcept;

        [[nodiscard]] bool isTerminal() const noexcept;

        [[nodiscard]] uint32_t getOrder();
    };
}
