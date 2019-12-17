#pragma once

#include <memory>
#include <optional>
#include <string>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "misc/helpers.h"
#include "type.h"
#include "value.h"

namespace ionir
{
class Pass;

class GlobalVar : public Construct
{
protected:
    Ptr<Type> type;

    std::string id;

    std::optional<Ptr<Value>> value;

public:
    GlobalVar(Ptr<Type> type, std::string id, std::optional<Ptr<Value>> value = std::nullopt);

    Ptr<Construct> accept(Pass *visitor) override;

    Ptr<Type> getType() const;

    void setType(Ptr<Type> type);

    std::string getId() const;

    void setId(std::string id);

    std::optional<Ptr<Value>> getValue() const;
};
} // namespace ionir
