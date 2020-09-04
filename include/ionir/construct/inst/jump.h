#pragma once

#include <optional>
#include <ionir/misc/ref.h>

namespace ionir {
    class Pass;

    class BasicBlock;

    struct JumpInstOpts : InstOpts {
        ionshared::Ptr<BasicBlock> basicBlockTarget;
    };

    class JumpInst : public Inst {
    private:
        ionshared::Ptr<BasicBlock> basicBlockTarget;

    public:
        explicit JumpInst(const JumpInstOpts &opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        [[nodiscard]] ionshared::Ptr<BasicBlock> getBasicBlockTarget() const noexcept;

        void setBasicBlockTarget(ionshared::Ptr<BasicBlock> basicBlockTarget) noexcept;
    };
}
