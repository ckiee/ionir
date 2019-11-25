#pragma once

#include <vector>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "value.h"
#include "inst_kind.h"

namespace ionir
{
class LlvmVisitor;

class Inst : public Node
{
protected:
    InstKind kind;

    std::vector<Value *> args;

public:
    Inst(InstKind kind, std::vector<Value *> args);

    Node *accept(LlvmVisitor *visitor) override;

    InstKind getKind() const;

    std::vector<Value *> getArgs() const;
};
} // namespace ionir
