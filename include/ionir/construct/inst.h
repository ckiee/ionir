#pragma once

#include <ionir/construct/value.h>
#include <ionir/construct/pseudo/child_construct.h>
#include <ionir/misc/helpers.h>

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

        ionshared::OptPtr<Inst> yields;

    public:
        Inst(
            ionshared::Ptr<BasicBlock> parent,
            InstKind kind, ionshared::OptPtr<Inst> yields = std::nullopt
        );

        void accept(Pass &visitor) override = 0;

        InstKind getInstKind() const noexcept;

        ionshared::OptPtr<Inst> getYields() const noexcept;

        bool isTerminal() const noexcept;

        uint32_t getOrder();
    };
}
