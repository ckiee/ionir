#pragma once

#include <memory>
#include <vector>
#include "ast_nodes/insts/goto.h"
#include "ast_nodes/inst.h"
#include "misc/helpers.h"
#include "pass.h"

namespace ionir
{
class PartialResolverPass : public Pass
{
protected:
    std::vector<Ptr<Inst>> partials;

    void resolveGotoInst(Ptr<GotoInst> partial);

public:
    PartialResolverPass(std::vector<Ptr<Inst>> partials);

    std::vector<Ptr<Inst>> getPartials() const;

    Ptr<Node> visitGotoInst(Ptr<GotoInst> node);
};
} // namespace ionir
