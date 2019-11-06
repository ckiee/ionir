#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
class BinaryExpr : public Node
{
protected:
    Node *leftSide;

    Node *rightSide;

public:
    BinaryExpr(Node *leftSide, Node *rightSide);

    Node *accept(LlvmVisitor *visitor) override;

    Node *getLeftSide() const;

    Node *getRightSide() const;
};
} // namespace ionir
