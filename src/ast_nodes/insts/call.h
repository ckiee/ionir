#pragma once

#include <memory>
#include <optional>
#include <string>
#include "parsing/partial_inst.h"
#include "parsing/scope.h"
#include "ast_nodes/function.h"

namespace ionir
{
class Pass;

class CallInst : public PartialInst<std::shared_ptr<Function>>
{
protected:
    std::string target;

public:
    CallInst(std::shared_ptr<Scope> scope, std::string target, std::optional<std::shared_ptr<Function>> callee = std::nullopt);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    std::string getTarget() const;

    void setTarget(std::string target);

    std::optional<std::shared_ptr<Function>> getCallee() const;

    void setCallee(std::shared_ptr<Function> callee);
};
} // namespace ionir
