#pragma once

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
