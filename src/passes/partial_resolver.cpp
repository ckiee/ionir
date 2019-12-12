#include <exception>
#include "partial_resolver.h"
#include "parsing/scope.h"
#include "ast_nodes/function.h"

namespace ionir
{
PartialResolverPass::PartialResolverPass(std::vector<std::shared_ptr<Inst>> partials)
    : partials(partials)
{
    //
}

std::vector<std::shared_ptr<Inst>> PartialResolverPass::getPartials() const
{
    return this->partials;
}

std::shared_ptr<Node> PartialResolverPass::visitGotoInst(std::shared_ptr<GotoInst> node)
{
    // Partial has already been resolved. Do not continue.
    if (node->isResolved())
    {
        return node;
    }

    std::shared_ptr<Scope> scope = node->getScope();

    switch (scope->getKind())
    {
    case ScopeKind::Block:
    {
        std::shared_ptr<Block> block = scope->unwrap()->staticCast<Block>();
        std::vector<std::shared_ptr<Section>> sections = block->getSections();

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
