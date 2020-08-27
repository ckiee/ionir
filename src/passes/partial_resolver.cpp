#include <ionir/passes/partial_resolver.h>

namespace ionir {
    PartialResolverPass::PartialResolverPass(std::vector<ionshared::Ptr<Inst>> partials) :
        partials(std::move(partials)) {
        //
    }

    std::vector<ionshared::Ptr<Inst>> PartialResolverPass::getPartials() const {
        return this->partials;
    }

// void PartialResolverPass::visitGotoInst(ionshared::Ptr<GotoInst> node)
// {
//     // Partial has already been resolved. Do not continue.
//     if (node->isResolved())
//     {
//         return;
//     }

//     ionshared::Ptr<Scope> scope = node->getScope();

//     switch (scope->getKind())
//     {
//     case ScopeKind::Block:
//     {
//         ionshared::Ptr<Block> block = scope->unwrap()->dynamicCast<Block>();
//         std::vector<ionshared::Ptr<Section>> sections = block->getSections();

//         for (auto section : sections)
//         {
//             // Resolve goto instruction with target section if applicable.
//             if (section->getId() == node->getTarget())
//             {
//                 node->resolve(section);

//                 // Node was resolved, no need to continue.
//                 return;
//             }
//         }

//         // No such target was encountered.
//         throw std::runtime_error("No block target was encountered for goto instruction");
//     }

//     default:
//     {
//         throw std::runtime_error("Unknown scope kind");
//     }
//     }
// }
}
