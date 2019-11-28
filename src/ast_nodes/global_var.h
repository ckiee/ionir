#pragma once

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
    Type *type;

    std::string identifier;

    std::optional<Value *> value;

public:
    GlobalVar(Type *type, std::string identifier, std::optional<Value *> value = std::nullopt);

    Node *accept(Pass *visitor) override;

    Type *getType() const;

    std::string getIdentifier() const;

    std::optional<Value *> getValue() const;
};
} // namespace ionir
