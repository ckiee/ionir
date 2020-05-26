#pragma once

#include <optional>
#include <ionir/misc/helpers.h>
#include <ionir/construct/pseudo/ref.h>

namespace ionir {
    class Pass;

    class BasicBlock;

    struct BranchInstOpts : InstOpts {
        Ptr<Construct> condition;

        PtrRef<BasicBlock> bodyRef;

        PtrRef<BasicBlock> otherwiseRef;
    };

    class BranchInst : public Inst {
    private:
        Ptr<Construct> condition;

        PtrRef<BasicBlock> bodySectionRef;

        PtrRef<BasicBlock> otherwiseSectionRef;

    public:
        explicit BranchInst(BranchInstOpts opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr<Construct> getCondition() const;

        void setCondition(Ptr<Construct> condition);

        PtrRef<BasicBlock> getBodyRef() const;

        void setBodyRef(PtrRef<BasicBlock> bodyRef);

        PtrRef<BasicBlock> getOtherwiseRef() const;

        void setOtherwiseRef(PtrRef<BasicBlock> otherwiseRef);
    };
}
