#pragma once

#include "ast_nodes/value.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class BooleanValue : public Value
{
protected:
    bool value;

public:
    BooleanValue(bool value);

    Ptr<Node> accept(Pass *visitor) override;

    bool getValue() const;

    void setValue(bool value);
};
} // namespace ionir
