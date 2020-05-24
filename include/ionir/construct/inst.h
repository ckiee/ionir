#pragma once

#include <ionir/construct/value.h>
#include <ionir/construct/child_construct.h>
#include <ionir/misc/helpers.h>
#include <ionir/llvm/llvm_inst.h>

namespace ionir {
    class Pass;

    class Section;

    typedef ChildConstructOpts<Section> InstOpts;

    enum class InstKind {
        Alloca,

        Store,

        Call,

        Return,

        Break,

        Branch
    };

    class Inst : public ChildConstruct<Section>, public OptPtrWrapper<LlvmInst> {
    private:
        InstKind kind;

    public:
        Inst(Ptr<Section> parent, InstKind kind);

        virtual void accept(Pass &visitor) = 0;

        InstKind getInstKind() noexcept;

        bool isTerminal() const noexcept;
    };
}
