#pragma once

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
