#pragma once

#include <memory>
#include "constructs/construct.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Expr : public Construct
{
protected:
    ExprKind kind;

public:
    Expr(std::vector<Ptr<Section>> sections = {});

    Ptr<Construct> accept(Pass *visitor) override;

    bool verify() const override;

    std::optional<Ptr<Section>> getEntrySection();

    std::vector<Ptr<Section>> getSections() const;
};
} // namespace ionir
