#pragma once

#include <optional>
#include <ionir/construct/expr.h>
#include <ionir/construct/pseudo/partial_inst.h>
#include <ionir/construct/section.h>
#include <ionir/misc/helpers.h>
#include <ionir/construct/pseudo/ref.h>

namespace ionir {
    class Pass;

    struct BranchInstOpts : InstOpts {
        Ptr<Expr<>> condition;

        PtrRef<Section> body;

        OptPtrRef<Section> otherwise = std::nullopt;
    };

    class BranchInst : public Inst {
    private:
        Ptr<Expr<>> condition;

        PtrRef<Section> body;

        OptPtrRef<Section> otherwise;

    public:
        explicit BranchInst(BranchInstOpts opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr<Expr<>> getCondition() const;

        void setCondition(Ptr<Expr<>> condition);

        PtrRef<Section> getBody() const;

        void setBody(PtrRef<Section> body);

        OptPtrRef<Section> getOtherwise() const;

        void setOtherwise(OptPtrRef<Section> otherwise);
    };
}
