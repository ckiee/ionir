#pragma once

#include <vector>
#include "ast_nodes/insts/goto.h"
#include "ast_nodes/inst.h"
#include "pass.h"

namespace ionir
{
class PartialResolverPass : public Pass
{
protected:
    std::vector<Inst *> partials;

    void resolveGotoInst(GotoInst *partial);

public:
    PartialResolverPass(std::vector<Inst *> partials);

    std::vector<Inst *> getPartials() const;

    Node *visitGotoInst(GotoInst *node);
};
} // namespace ionir
