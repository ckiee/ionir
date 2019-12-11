#pragma once

#include <memory>
#include "ast_nodes/value.h"

namespace ionir
{
class Pass;

class CharValue : public Value
{
protected:
    char value;

public:
    CharValue(char value);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    char getValue() const;

    void setValue(char value);
};
} // namespace ionir
