#include <exception>
#include "partial_resolver.h"
#include "parsing/scope.h"
#include "ast_nodes/function.h"

namespace ionir
{
void PartialResolverPass::resolvePartial(PartialInst *partial)
{
    Scope *scope = partial->getScope();

    switch (scope->getKind())
    {
    case ScopeKind::Function:
    {
        Function *function = (Function *)scope->unwrap();

        // TODO

        throw std::runtime_error("Not implemented");
    }

    default:
    {
        throw std::runtime_error("Encountered unknown scope kind");
    }
    }
}
} // namespace ionir
