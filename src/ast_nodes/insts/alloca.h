#pragma once

#include <string>
#include "ast_nodes/inst.h"
#include "ast_nodes/inst_kind.h"
#include "ast_nodes/type.h"

namespace ionir
{
class AllocaInst : public Inst
{
protected:
    std::string id;

    Type *type;

public:
    // TODO: Missing support for array type allocas.
    AllocaInst(std::string id, Type *type);

    Node *accept(Pass *visitor) override;

    std::string getId() const;

    Type *getType() const;
};
} // namespace ionir
