#include <optional>
#include "ast_nodes/section.h"
#include "semantic_analysis.h"
#include "ast_nodes/inst_kind.h"
#include "ast_nodes/insts/return.h"

namespace ionir
{
std::shared_ptr<Node> SemanticAnalysisPass::visitFunction(std::shared_ptr<Function> node)
{
    // TODO: Hard-coded id.
    if (node->getPrototype()->getReturnType()->getId() != "void")
    {
        std::optional<std::shared_ptr<Section>> entrySection = node->getBody()->getEntrySection();

        if (!entrySection.has_value())
        {
            throw std::runtime_error("Entry section for function body is not set");
        }

        for (auto inst : (*entrySection)->getInsts())
        {
            if (inst->getInstKind() == InstKind::Return)
            {
                std::shared_ptr<ReturnInst> returnInst = inst->cast<ReturnInst>();

                if (!returnInst->getValue().has_value())
                {
                    throw std::runtime_error("Function whose prototype's return type is not void must return a corresponding value");
                }
            }
        }
    }
}
} // namespace ionir
