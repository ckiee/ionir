#include <exception>
#include "partial_resolver.h"
#include "parsing/scope.h"
#include "ast_constructs/function.h"

namespace ionir
{
PartialResolverPass::PartialResolverPass(std::vector<Ptr<Inst>> partials)
    : partials(partials)
{
    //
}

std::vector<Ptr<Inst>> PartialResolverPass::getPartials() const
{
    return this->partials;
}

Ptr<Construct> PartialResolverPass::visitGotoInst(Ptr<GotoInst> node)
{
    // Partial has already been resolved. Do not continue.
    if (node->isResolved())
    {
        return node;
    }

    Ptr<Scope> scope = node->getScope();

    switch (scope->getKind())
    {
    case ScopeKind::Block:
    {
        Ptr<Block> block = scope->unwrap()->cast<Block>();
        std::vector<Ptr<Section>> sections = block->getSections();

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
        throw std::runtime_error("Unknown scope kind");
    }
    }

    return node;
}
} // namespace ionir
