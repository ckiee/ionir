#pragma once

#include <vector>
#include <string>
#include "code_gen/node.h"
#include "section.h"

namespace ionir
{
class Pass;

class Block : public Node
{
protected:
    std::string identifier;

    std::vector<Section *> insts;

public:
    Block(std::string identifier, std::vector<Section *> sections = {});

    Node *accept(Pass *visitor) override;

    std::vector<PartialInst *> getInsts() const;

    std::string getIdentifier() const;
};
} // namespace ionir
