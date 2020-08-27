#pragma once

#include <optional>
#include <ionir/misc/helpers.h>
#include <ionir/construct/pseudo/ref.h>

namespace ionir {
    class Pass;

    class BasicBlock;

    struct JumpInstOpts : InstOpts {
        PtrRef<BasicBlock> blockRef;
    };

    class JumpInst : public Inst {
    private:
        PtrRef<BasicBlock> blockRef;

    public:
        explicit JumpInst(const JumpInstOpts &opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        [[nodiscard]] PtrRef<BasicBlock> getBlockRef() const;

        void setBlockRef(PtrRef<BasicBlock> blockRef);
    };
}
