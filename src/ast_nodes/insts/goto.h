#pragma once

#include <memory>
#include <optional>
#include <string>
#include "parsing/partial_inst.h"
#include "parsing/scope.h"
#include "ast_nodes/section.h"

namespace ionir
{
class Pass;

class GotoInst : public PartialInst<std::shared_ptr<Section>>
{
protected:
    std::string target;

public:
    GotoInst(Scope *scope, std::string target, std::optional<std::shared_ptr<Section>> section = std::nullopt);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    std::string getTarget() const;

    void setTarget(std::string target);

    std::optional<std::shared_ptr<Section>> getSection() const;

    void setSection(std::shared_ptr<Section> section);
};
} // namespace ionir
