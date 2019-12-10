#pragma once

#include <memory>
#include <optional>
#include <string>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "type.h"
#include "value.h"

namespace ionir
{
class Pass;

class GlobalVar : public Node
{
protected:
    std::shared_ptr<Type> type;

    std::string id;

    std::optional<std::shared_ptr<Value>> value;

public:
    GlobalVar(std::shared_ptr<Type> type, std::string id, std::optional<std::shared_ptr<Value>> value = std::nullopt);

    ~GlobalVar();

    Node *accept(Pass *visitor) override;

    std::shared_ptr<Type> getType() const;

    std::string getId() const;

    std::optional<std::shared_ptr<Value>> getValue() const;
};
} // namespace ionir
