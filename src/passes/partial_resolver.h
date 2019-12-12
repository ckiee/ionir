#pragma once

#include <memory>
#include <vector>
#include "ast_nodes/insts/goto.h"
#include "ast_nodes/inst.h"
#include "pass.h"

namespace ionir
{
class PartialResolverPass : public Pass
{
protected:
    std::vector<std::shared_ptr<Inst>> partials;

    void resolveGotoInst(std::shared_ptr<GotoInst> partial);

public:
    PartialResolverPass(std::vector<std::shared_ptr<Inst>> partials);

    std::vector<std::shared_ptr<Inst>> getPartials() const;

    std::shared_ptr<Node> visitGotoInst(std::shared_ptr<GotoInst> node);
};
} // namespace ionir
