#pragma once

#include <string>
#include "ast_nodes/inst.h"
#include "ast_nodes/inst_kind.h"
#include "ast_nodes/type.h"
#include "ast_nodes/value.h"

namespace ionir
{
class Pass;

class ReturnInst : public Inst
{
protected:
    Value *value;

public:
    ReturnInst(Value *value);

    Node *accept(Pass *visitor) override;

    Value *getValue() const;
};
} // namespace ionir
