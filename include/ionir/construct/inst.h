#pragma once

#include <ionir/construct/value.h>
#include <ionir/construct/child_construct.h>
#include <ionir/misc/helpers.h>
#include <ionir/llvm/llvm_inst.h>

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

        Icmp
    };

    class Inst : public ChildConstruct<BasicBlock> {
    private:
        InstKind kind;

        ionshared::OptPtr<Inst> yields;

    public:
        Inst(ionshared::Ptr<BasicBlock> parent, InstKind kind, ionshared::OptPtr<Inst> yields = std::nullopt);

        virtual void accept(Pass &visitor) = 0;

        InstKind getInstKind() const noexcept;

        ionshared::OptPtr<Inst> getYields() const noexcept;

        bool isTerminal() const noexcept;
    };
}
