#pragma once

#include <optional>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class LlvmVisitor;

class BinaryExpr : public Node
{
protected:
    Node *leftSide;

    std::optional<Node *> rightSide;

public:
    BinaryExpr(Node *leftSide, std::optional<Node *> rightSide = std::nullopt);

    Node *accept(LlvmVisitor *visitor) override;

    Node *getLeftSide() const;

    std::optional<Node *> getRightSide() const;
};
} // namespace ionir
