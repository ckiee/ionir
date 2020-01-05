#pragma once

#include <ionir/construct/value/value.h>
#include <ionir/construct/child_construct.h>
#include <ionir/misc/helpers.h>

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

    class Inst : public ChildConstruct<Section> {
    private:
        InstKind kind;

    public:
        Inst(Ptr<Section> parent, InstKind kind);

        virtual void accept(Pass &visitor) = 0;

        InstKind getInstKind();
    };
}
