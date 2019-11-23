#include "type.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
Type::Type(std::string identifier, bool isPointer)
    : Node(NodeKind::Type), identifier(identifier), isPointer(isPointer)
{
    //
}

Node *Type::accept(LlvmVisitor *visitor)
{
    return visitor->visitType(this);
}

std::string Type::getIdentifier() const
{
    return this->identifier;
}

bool Type::getIsPointer() const
{
    return this->isPointer;
}
} // namespace ionir
