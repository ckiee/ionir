#pragma once

#include "ast_nodes/inst.h"
#include "ast_nodes/block.h"

namespace ionir
{
class GotoInst : public Inst
{
protected:
    Block *block;

public:
    GotoInst(Block *block);

    Block *getBlock() const;
};
} // namespace ionir
