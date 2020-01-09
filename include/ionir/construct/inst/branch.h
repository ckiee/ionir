#pragma once

#include <optional>
#include <ionir/construct/expr.h>
#include <ionir/construct/pseudo/partial_inst.h>
#include <ionir/construct/section.h>
#include <ionir/misc/helpers.h>
#include <ionir/construct/pseudo/reference.h>

namespace ionir {
    class Pass;

    struct BranchInstOpts : InstOpts {
        Ptr<Expr> condition;

        Ptr<Reference<Section>> body;

        std::optional<Ptr<Reference<Section>>> otherwise = std::nullopt;
    };

    class BranchInst : public Inst {
    private:
        Ptr<Expr> condition;

        Ptr<Reference<Section>> body;

        std::optional<Ptr<Reference<Section>>> otherwise;

    public:
        explicit BranchInst(BranchInstOpts opts);

        void accept(Pass &visitor) override;

        Ptr<Expr> getCondition() const;

        void setCondition(Ptr<Expr> condition);

        Ptr<Reference<Section>> getBody() const;

        void setBody(Ptr<Reference<Section>> body);

        std::optional<Ptr<Reference<Section>>> getOtherwise() const;

        void setOtherwise(std::optional<Ptr<Reference<Section>>> otherwise);
    };
}
