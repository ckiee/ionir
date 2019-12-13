#include <vector>
#include "parsing/driver.h"
#include "code_gen/node_kind.h"
#include "pass_manager.h"

namespace ionir
{
PassManager::PassManager() : passes({})
{
    //
}

void PassManager::registerPass(std::shared_ptr<PassManagerItem> item)
{
    this->passes.push_back(item);
}

void PassManager::run(Ast ast)
{
    for (auto item : this->passes)
    {
        // TODO: Process priorities.
        for (auto topLevelNode : ast)
        {
            item->pass->visit(topLevelNode);
        }
    }
}
} // namespace ionir
