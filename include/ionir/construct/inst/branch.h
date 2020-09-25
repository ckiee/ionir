#pragma once

#include <optional>

namespace ionir {
    class Pass;

    class BasicBlock;

    struct BranchInstOpts : InstOpts {
        ionshared::Ptr<Construct> condition;

        ionshared::Ptr<BasicBlock> consequentBasicBlock;

        ionshared::Ptr<BasicBlock> alternativeBasicBlock;
    };

    class BranchInst : public Inst {
    private:
        ionshared::Ptr<Construct> condition;

        ionshared::Ptr<BasicBlock> consequentBasicBlock;

        ionshared::Ptr<BasicBlock> alternativeBasicBlock;

    public:
        explicit BranchInst(const BranchInstOpts &opts);

        void accept(Pass &visitor) override;

        Ast getChildrenNodes() override;

        [[nodiscard]] ionshared::Ptr<Construct> getCondition() const noexcept;

        void setCondition(ionshared::Ptr<Construct> condition) noexcept;

        [[nodiscard]] ionshared::Ptr<BasicBlock> getConsequentBasicBlock() const noexcept;

        void setConsequentBasicBlock(ionshared::Ptr<BasicBlock> consequentBasicBlock) noexcept;

        [[nodiscard]] ionshared::Ptr<BasicBlock> getAlternativeBasicBlock() const noexcept;

        void setAlternativeBasicBlock(ionshared::Ptr<BasicBlock> alternativeBasicBlock) noexcept;
    };
}
