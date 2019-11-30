#pragma once

#include "parsing/partial_inst.h"
#include "parsing/scope.h"
#include "ast_nodes/block.h"

namespace ionir
{
class Pass;

class GotoInst : public PartialInst<Block *>
{
public:
    GotoInst(Scope *scope, std::optional<Block *> block = std::nullopt);

    Node *accept(Pass *visitor) override;

    std::optional<Block *> getBlock() const;
};
} // namespace ionir
