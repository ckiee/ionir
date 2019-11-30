#include <exception>
#include "partial_resolver.h"
#include "parsing/scope.h"
#include "ast_nodes/function.h"

namespace ionir
{
PartialResolverPass::PartialResolverPass(std::vector<Inst *> partials)
    : partials(partials)
{
    //
}

std::vector<Inst *> PartialResolverPass::getPartials() const
{
    return this->partials;
}

Node *PartialResolverPass::visitGotoInst(GotoInst *node)
{
    // Partial has already been resolved. Do not continue.
    if (node->isResolved())
    {
        return node;
    }

    // TODO

    return node;
}
} // namespace ionir
