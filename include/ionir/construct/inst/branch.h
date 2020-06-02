#pragma once

#include <optional>
#include <ionir/misc/helpers.h>
#include <ionir/construct/pseudo/ref.h>

namespace ionir {
    class Pass;

    class BasicBlock;

    struct BranchInstOpts : InstOpts {
        Ptr<Construct> condition;

        PtrRef<BasicBlock> blockRef;

        PtrRef<BasicBlock> otherwiseRef;
    };

    class BranchInst : public Inst {
    private:
        Ptr<Construct> condition;

        PtrRef<BasicBlock> blockRef;

        PtrRef<BasicBlock> otherwiseBlockRef;

    public:
        explicit BranchInst(BranchInstOpts opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        Ptr<Construct> getCondition() const;

        void setCondition(Ptr<Construct> condition);

        PtrRef<BasicBlock> getBlockRef() const;

        void setBlockRef(PtrRef<BasicBlock> blockRef);

        PtrRef<BasicBlock> getOtherwiseBlockRef() const;

        void setOtherwiseBlockRef(PtrRef<BasicBlock> otherwiseBlockRef);
    };
}
