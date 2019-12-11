#pragma once

#include <memory>
#include <string>
#include "ast_nodes/value.h"

namespace ionir
{
class Pass;

class StringValue : public Value
{
protected:
    std::string value;

public:
    StringValue(std::string value);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    std::string getValue() const;

    void setValue(std::string value);
};
} // namespace ionir
