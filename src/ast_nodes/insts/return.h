#pragma once

#include <string>
#include "ast_nodes/inst.h"
#include "ast_nodes/inst_kind.h"
#include "ast_nodes/type.h"
#include "ast_nodes/value.h"

namespace ionir
{
class ReturnInst : public Inst
{
protected:
    Value *value;

public:
    ReturnInst(Value *value);

    Value *getValue() const;
};
} // namespace ionir
