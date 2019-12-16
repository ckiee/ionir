#pragma once

#include <memory>
#include "code_gen/node.h"
#include "ast_nodes/function.h"
#include "pass.h"

namespace ionir
{
class SemanticAnalysisPass : public Pass
{
public:
    SemanticAnalysisPass();

    void functionReturnCheck(std::shared_ptr<Function> node);

    std::shared_ptr<Node> visitFunction(std::shared_ptr<Function> node) override;
};
} // namespace ionir
