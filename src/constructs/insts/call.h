#pragma once

#include <memory>
#include <optional>
#include <string>
#include "constructs/psuedo/partial_inst.h"
#include "parsing/scope.h"
#include "constructs/function.h"
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

    Ptr<Construct> accept(Pass *visitor) override;

    std::string getTarget() const;

    std::optional<Ptr<Function>> getCallee() const;
};
} // namespace ionir
