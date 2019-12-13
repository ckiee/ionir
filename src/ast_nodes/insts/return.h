#pragma once

#include <memory>
#include <string>
#include "ast_nodes/inst.h"
#include "ast_nodes/inst_kind.h"
#include "ast_nodes/type.h"
#include "ast_nodes/value.h"

namespace ionir
{
class Pass;

class ReturnInst : public Inst
{
protected:
    std::optional<std::shared_ptr<Value>> value;

public:
    ReturnInst(std::optional<std::shared_ptr<Value>> value = std::nullopt);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    std::optional<std::shared_ptr<Value>> getValue() const;

    void setValue(std::optional<std::shared_ptr<Value>> value);
};
} // namespace ionir
