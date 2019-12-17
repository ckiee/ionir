#pragma once

#include <optional>
#include <memory>
#include <string>
#include "ast_constructs/inst.h"
#include "ast_constructs/inst_kind.h"
#include "ast_constructs/type.h"
#include "ast_constructs/value.h"
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

    void setValue(std::optional<Ptr<Value>> value);
};
} // namespace ionir
