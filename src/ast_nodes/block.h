#pragma once

#include <vector>
#include <string>
#include "code_gen/node.h"
#include "code_gen/node_type.h"

namespace ionir
{
class Block : public Node
{
private:
    std::string identifier;

    std::vector<Node> insts;

public:
    Block(std::string identifier, std::vector<Node> insts) : Node(NodeType::Block)
    {
        this->identifier = identifier;
        this->insts = insts;
    }

    Node accept(LlvmVisitor *visitor)
    {
        return visitor->visitBlock(this);
    }

    std::vector<Node> getInsts() const
    {
        return this->insts;
    }

    std::string getIdentifier() const
    {
        return this->identifier;
    }
};
} // namespace ionir
