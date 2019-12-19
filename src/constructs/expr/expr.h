#pragma once

#include <memory>
#include "constructs/construct.h"
#include "misc/helpers.h"
#include "expr_kind.h"

namespace ionir
{
class Pass;

class Expr : public Construct
{
protected:
    ExprKind exprKind;

public:
    Expr(ExprKind kind);

    virtual void accept(Pass *visitor) = 0;

    ExprKind getExprKind() const;
};
} // namespace ionir
