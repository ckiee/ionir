#pragma once

#include <optional>
#include <ionir/construct/expr/expr.h>
#include <ionir/construct/psuedo/partial_inst.h>
#include <ionir/construct/section.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass;

    struct BranchInstPartials {
        Ptr<Section> body;

        std::optional<Ptr<Section>> otherwise = std::nullopt;
    };

    struct BranchInstOpts : InstOpts {
        Ptr<Expr> condition;

        Ptr<Section> body;

        std::optional<Ptr<Section>> otherwise = std::nullopt;
    };

    class BranchInst : public PartialInst<BranchInstPartials> {
    private:
        Ptr<Expr> condition;

        Ptr<Section> body;

        std::optional<Ptr<Section>> otherwise;

    public:
        BranchInst(BranchInstOpts opts);

        void accept(Pass *visitor) override;

        Ptr<Expr> getCondition() const;

        void setCondition(Ptr<Expr> condition);

        Ptr<Section> getBody() const;

        void setBody(Ptr<Section> body);

        std::optional<Ptr<Section>> getOtherwise() const;

        void setOtherwise(std::optional<Ptr<Section>> otherwise);
    };
}
