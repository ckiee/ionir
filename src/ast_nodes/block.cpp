#include <vector>
#include <string>
#include "block.h"
#include "code_gen/llvm_visitor.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
Block::Block(std::string identifier, std::vector<Node> insts)
    : Node(NodeKind::Block), identifier(identifier), insts(insts)
{
    //
}

Node *Block::accept(LlvmVisitor *visitor)
{
    return visitor->visitBlock(this);
}

std::vector<Node> Block::getInsts() const
{
    return this->insts;
}

std::string Block::getIdentifier() const
{
    return this->identifier;
}
} // namespace ionir
