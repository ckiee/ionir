#include "type.h"

namespace ionir
{
Type::Type(bool isPointer) : Node(NodeKind::Type), isPointer(isPointer)
{
    //
}

Node *Type::accept(LlvmVisitor *visitor)
{
    return visitor->visitType(this);
}

bool Type::getIsPointer() const
{
    return this->isPointer;
}
} // namespace ionir
