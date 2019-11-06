#pragma once

namespace ionir
{
class Block : public Node
{
private:
    std::string identifier;

    std::vector<Node> insts;

public:
    Block(std::string identifier, std::vector<Node> insts);

    Node *accept(LlvmVisitor *visitor) override;

    std::vector<Node> getInsts() const;

    std::string getIdentifier() const;
};
} // namespace ionir
