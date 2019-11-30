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

    virtual Node *accept(Pass *visitor) = 0;

    InstKind getInstKind() const;
};
} // namespace ionir
