#pragma once

#include <memory>
#include "ast_nodes/value.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class CharValue : public Value
{
protected:
    char value;

public:
    CharValue(char value);

    Ptr<Node> accept(Pass *visitor) override;

    char getValue() const;

    void setValue(char value);
};
} // namespace ionir
