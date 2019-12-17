#pragma once

#include <memory>
#include <optional>
#include <string>
#include "parsing/partial_inst.h"
#include "parsing/scope.h"
#include "constructs/section.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class GotoInst : public PartialInst<Ptr<Section>>
{
protected:
    std::string target;

public:
    GotoInst(Ptr<Scope> scope, std::string target, std::optional<Ptr<Section>> section = std::nullopt);

    Ptr<Construct> accept(Pass *visitor) override;

    std::string getTarget() const;

    void setTarget(std::string target);

    std::optional<Ptr<Section>> getSection() const;

    void setSection(Ptr<Section> section);
};
} // namespace ionir
