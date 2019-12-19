#pragma once

#include <memory>
#include "constructs/construct.h"
#include "constructs/function.h"
#include "misc/helpers.h"
#include "pass.h"

namespace ionir
{
class SemanticAnalysisPass : public Pass
{
public:
    SemanticAnalysisPass();

    void functionReturnCheck(Ptr<Function> node);

    Ptr<Construct> visitFunction(Ptr<Function> node) override;
};
} // namespace ionir
