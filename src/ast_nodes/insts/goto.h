#pragma once

#include <string>
#include "parsing/partial_inst.h"
#include "parsing/scope.h"
#include "ast_nodes/section.h"

namespace ionir
{
class Pass;

class GotoInst : public PartialInst<Section *>
{
protected:
    std::string target;

public:
    GotoInst(Scope *scope, std::string target, std::optional<Section *> section = std::nullopt);

    Node *accept(Pass *visitor) override;

    std::string getTarget() const;

    std::optional<Section *> getSection() const;
};
} // namespace ionir
