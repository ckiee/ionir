#pragma once

#include <ionir/construct/value.h>
#include <ionir/construct/pseudo/child_construct.h>

namespace ionir {
    class Pass;

    class BasicBlock;

    typedef ChildConstructOpts<BasicBlock> InstOpts;

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

    class Inst : public ChildConstruct<BasicBlock> {
    private:
        InstKind kind;

    public:
        Inst(ionshared::Ptr<BasicBlock> parent, InstKind kind);

        void accept(Pass &visitor) override = 0;

        [[nodiscard]] InstKind getInstKind() const noexcept;

        [[nodiscard]] bool isTerminal() const noexcept;

        [[nodiscard]] uint32_t getOrder();
    };
}
