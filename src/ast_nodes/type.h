#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class LlvmVisitor;

class Type : public Node
{
protected:
    bool isPointer;

public:
    Type(bool isPointer);

    Node *accept(LlvmVisitor *visitor) override;

    bool getIsPointer() const;
};
} // namespace ionir
