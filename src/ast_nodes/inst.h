#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "value.h"
#include "inst_kind.h"

namespace ionir
{
class Pass;

class Inst : public Node
{
protected:
    InstKind kind;

public:
    Inst(InstKind kind);

    Node *accept(Pass *visitor) override;

    InstKind getInstKind() const;
};
} // namespace ionir
