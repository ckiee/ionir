#include "block.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
Block::Block(std::string identifier, std::vector<PartialInst *> insts)
    : Node(NodeKind::Block), identifier(identifier), insts(insts)
{
    //
}

Node *Block::accept(LlvmVisitor *visitor)
{
    return visitor->visitBlock(this);
}

std::vector<PartialInst *> Block::getInsts() const
{
    return this->insts;
}

std::string Block::getIdentifier() const
{
    return this->identifier;
}
} // namespace ionir
