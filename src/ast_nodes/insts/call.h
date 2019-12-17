#pragma once

#include <memory>
#include <optional>
#include <string>
#include "parsing/partial_inst.h"
#include "parsing/scope.h"
#include "ast_nodes/function.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class CallInst : public PartialInst<Ptr<Function>>
{
protected:
    std::string target;

public:
    CallInst(Ptr<Scope> scope, std::string target, std::optional<Ptr<Function>> callee = std::nullopt);

    Ptr<Node> accept(Pass *visitor) override;

    std::string getTarget() const;

    void setTarget(std::string target);

    std::optional<Ptr<Function>> getCallee() const;

    void setCallee(Ptr<Function> callee);
};
} // namespace ionir
