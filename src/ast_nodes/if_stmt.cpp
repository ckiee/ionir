#include "if_stmt.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
IfStmt::IfStmt(Block *body, std::optional<Block *> otherwise)
    : Node(NodeKind::IfStatement), body(body), otherwise(otherwise)
{
    //
}

Node *IfStmt::accept(LlvmVisitor *visitor)
{
    return visitor->visitIfStmt(this);
}

BinaryExpr *IfStmt::getCondition() const
{
    return this->condition;
}

Block *IfStmt::getBody() const
{
    return this->body;
}

std::optional<Block *> IfStmt::getOtherwise() const
{
    return this->otherwise;
}
} // namespace ionir
