#pragma once

#include <optional>
#include <memory>
#include <string>
#include "constructs/inst.h"
#include "constructs/inst_kind.h"
#include "constructs/type.h"
#include "constructs/value.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class ReturnInst : public Inst
{
protected:
    std::optional<Ptr<Value>> value;

public:
    ReturnInst(std::optional<Ptr<Value>> value = std::nullopt);

    Ptr<Construct> accept(Pass *visitor) override;

    std::optional<Ptr<Value>> getValue() const;
};
} // namespace ionir
