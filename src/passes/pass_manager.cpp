#include <vector>
#include "parsing/driver.h"
#include "construct/construct_kind.h"
#include "pass_manager.h"

namespace ionir
{
PassManager::PassManager() : passes({})
{
    //
}

void PassManager::registerPass(Ptr<PassManagerItem> item)
{
    this->passes.push_back(item);
}

void PassManager::run(Ast ast)
{
    for (auto item : this->passes)
    {
        // TODO: Process priorities.
        for (auto topLevelConstruct : ast)
        {
            item->pass->visit(topLevelConstruct);
        }
    }
}
} // namespace ionir
