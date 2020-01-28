#pragma once

#include <optional>
#include <ionir/construct/expr.h>
#include <ionir/construct/pseudo/partial_inst.h>
#include <ionir/misc/helpers.h>
#include <ionir/construct/pseudo/ref.h>

namespace ionir {
    class Pass;

    class Section;

    struct BranchInstOpts : InstOpts {
        Ptr<Expr<>> condition;

        PtrRef<Section> bodyRef;

        OptPtrRef<Section> otherwiseRef = std::nullopt;
    };

    class BranchInst : public Inst {
    private:
        Ptr<Expr<>> condition;

        PtrRef<Section> bodyRef;

        OptPtrRef<Section> otherwiseRef;

    public:
        explicit BranchInst(BranchInstOpts opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr<Expr<>> getCondition() const;

        void setCondition(Ptr<Expr<>> condition);

        PtrRef<Section> getBodyRef() const;

        void setBodyRef(PtrRef<Section> bodyRef);

        OptPtrRef<Section> getOtherwiseRef() const;

        void setOtherwiseRef(OptPtrRef<Section> otherwiseRef);
    };
}
