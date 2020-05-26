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

        Branch
    };

    class Inst : public ChildConstruct<BasicBlock> {
    private:
        InstKind kind;

    public:
        Inst(Ptr<BasicBlock> parent, InstKind kind);

        virtual void accept(Pass &visitor) = 0;

        InstKind getInstKind() noexcept;

        bool isTerminal() const noexcept;
    };
}
