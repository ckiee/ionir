#pragma once

#include <optional>
#include <ionir/misc/helpers.h>
#include <ionir/construct/pseudo/ref.h>

namespace ionir {
    class Pass;

    class BasicBlock;

    struct BranchInstOpts : InstOpts {
        ionshared::Ptr<Construct> condition;

        PtrRef<BasicBlock> blockRef;

        PtrRef<BasicBlock> otherwiseRef;
    };

    class BranchInst : public Inst {
    private:
        ionshared::Ptr<Construct> condition;

        PtrRef<BasicBlock> consequentBlockRef;

        PtrRef<BasicBlock> alternativeBlockRef;

    public:
        explicit BranchInst(const BranchInstOpts &opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        [[nodiscard]] ionshared::Ptr<Construct> getCondition() const;

        void setCondition(ionshared::Ptr<Construct> condition);

        [[nodiscard]] PtrRef<BasicBlock> getConsequentBlockRef() const;

        void setConsequentBlockRef(PtrRef<BasicBlock> blockRef);

        [[nodiscard]] PtrRef<BasicBlock> getAlternativeBlockRef() const;

        void setAlternativeBlockRef(PtrRef<BasicBlock> otherwiseBlockRef);
    };
}
