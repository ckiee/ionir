#pragma once

#include "construct/function.h"
#include "misc/helpers.h"
#include "pass.h"

namespace ionir
{
class SemanticAnalysisPass : public Pass
{
public:
    SemanticAnalysisPass();

    void functionReturnCheck(Ptr<Function> node);

    void visitFunction(Ptr<Function> node) override;
};
} // namespace ionir
