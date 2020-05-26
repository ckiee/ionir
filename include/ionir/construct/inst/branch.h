#pragma once

#include <optional>
#include <ionir/construct/expr.h>
#include <ionir/misc/helpers.h>
#include <ionir/construct/pseudo/ref.h>

namespace ionir {
    class Pass;

    class BasicBlock;

    struct BranchInstOpts : InstOpts {
        Ptr<Expr<>> condition;

        PtrRef<BasicBlock> bodyRef;

        PtrRef<BasicBlock> otherwiseRef;
    };

    class BranchInst : public Inst {
    private:
        Ptr<Expr<>> condition;

        PtrRef<BasicBlock> bodySectionRef;

        PtrRef<BasicBlock> otherwiseSectionRef;

    public:
        explicit BranchInst(BranchInstOpts opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr<Expr<>> getCondition() const;

        void setCondition(Ptr<Expr<>> condition);

        PtrRef<BasicBlock> getBodyRef() const;

        void setBodyRef(PtrRef<BasicBlock> bodyRef);

        PtrRef<BasicBlock> getOtherwiseRef() const;

        void setOtherwiseRef(PtrRef<BasicBlock> otherwiseRef);
    };
}
