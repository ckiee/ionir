#pragma once

#include <vector>
#include <string>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class LlvmVisitor;

class Block : public Node
{
private:
    std::string identifier;

    std::vector<Node *> insts;

public:
    Block(std::string identifier, std::vector<Node *> insts);

    Node *accept(LlvmVisitor *visitor) override;

    std::vector<Node *> getInsts() const;

    std::string getIdentifier() const;
};
} // namespace ionir
