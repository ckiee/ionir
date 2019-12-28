#pragma once

#include <optional>
#include <ionir/lexical/token_type.h>
#include <ionir/misc/helpers.h>
#include "expr.h"

namespace ionir {
    class Pass;

    class IdExpr : public Expr {
    public:
        IdExpr();

        void accept(Pass *visitor) override;
    };
}
