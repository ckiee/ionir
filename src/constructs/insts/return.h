#pragma once

#include <optional>
#include <memory>
#include <string>
#include "constructs/insts/inst.h"
#include "constructs/insts/inst_kind.h"
#include "constructs/type.h"
#include "constructs/values/value.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

struct ReturnInstOpts : InstOpts
{
    std::optional<Ptr<Value>> value = std::nullopt;
};

class ReturnInst : public Inst
{
protected:
    std::optional<Ptr<Value>> value;

public:
    ReturnInst(ReturnInstOpts opts);

    void accept(Pass *visitor) override;

    std::optional<Ptr<Value>> &getValue();

    void setValue(std::optional<Ptr<Value>> value);
};
} // namespace ionir
