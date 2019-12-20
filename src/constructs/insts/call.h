#pragma once

#include <memory>
#include <optional>
#include <string>
#include "constructs/psuedo/partial_inst.h"
#include "constructs/insts/partial_inst_opts.h"
#include "parsing/scope.h"
#include "constructs/function.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

struct CallInstOpts : PartialInstOpts
{
    std::string target;

    std::optional<Ptr<Function>> callee = std::nullopt;
};

class CallInst : public PartialInst<Ptr<Function>>
{
protected:
    std::string target;

public:
    CallInst(CallInstOpts opts);

    void accept(Pass *visitor) override;

    std::string getTarget() const;

    void setTarget(std::string target);

    std::optional<Ptr<Function>> getCallee() const;
};
} // namespace ionir
