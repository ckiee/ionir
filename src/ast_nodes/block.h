#pragma once

#include <vector>
#include <string>
#include "ast_nodes/inst.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class LlvmVisitor;

class Block : public Node
{
private:
    std::string identifier;

    std::vector<Inst *> insts;

public:
    Block(std::string identifier, std::vector<Inst *> insts = {});

    Node *accept(LlvmVisitor *visitor) override;

    std::vector<Inst *> getInsts() const;

    std::string getIdentifier() const;
};
} // namespace ionir
