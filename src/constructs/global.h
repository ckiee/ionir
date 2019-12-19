#pragma once

#include <memory>
#include <optional>
#include <string>
#include "constructs/construct.h"
#include "constructs/construct_kind.h"
#include "misc/helpers.h"
#include "type.h"
#include "value.h"

namespace ionir
{
class Pass;

class Global : public Construct
{
protected:
    Ptr<Type> type;

    std::string id;

    std::optional<Ptr<Value>> value;

public:
    Global(Ptr<Type> type, std::string id, std::optional<Ptr<Value>> value = std::nullopt);

    void accept(Pass *visitor) override;

    Ptr<Type> getType() const;

    std::string getId() const;

    std::optional<Ptr<Value>> getValue() const;
};
} // namespace ionir
