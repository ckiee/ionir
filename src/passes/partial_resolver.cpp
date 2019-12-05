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

    Scope *scope = node->getScope();

    switch (scope->getKind())
    {
    case ScopeKind::Block:
    {
        Block *block = (Block *)scope->unwrap();
        std::vector<Section *> sections = block->getSections();

        for (auto section : sections)
        {
            // Resolve goto instruction with target section if applicable.
            if (section->getId() == node->getTarget())
            {
                node->resolve(section);

                // Return resolved node, no need to continue.
                return node;
            }
        }

        // No such target was encountered.
        throw std::runtime_error("No block target was encountered for goto instruction");
    }

    default:
    {
        throw std::runtime_error("Encountered unsupported scope kind");
    }
    }

    return node;
}
} // namespace ionir
