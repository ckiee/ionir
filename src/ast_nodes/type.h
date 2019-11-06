#pragma once

#include "code_gen/llvm_visitor.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
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
