#pragma once

#include <string>
#include <vector>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "value.h"

namespace ionir
{
class LlvmVisitor;

class Inst : public Node
{
protected:
    std::string identifier;

    std::vector<Value *> args;

public:
    Inst(std::string identifier, std::vector<Value *> args);

    Node *accept(LlvmVisitor *visitor) override;

    std::string getIdentifier() const;

    std::vector<Value *> getArgs() const;
};
} // namespace ionir
