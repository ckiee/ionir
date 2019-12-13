#pragma once

#include <vector>
#include <memory>
#include "parsing/ast.h"
#include "pass_manager_item.h"

namespace ionir
{
class PassManager
{
protected:
    /**
     * Internal container on which pass 
     * manager items will be both stored
     * and processed from.
     */
    std::vector<std::unique_ptr<PassManagerItem>> passes;

public:
    PassManager();

    /**
     * Register a pass in the set. Returns whether
     * the provided pass was successfully registered
     * in the internal set.
     */
    void registerPass(std::unique_ptr<PassManagerItem> item);

    void run(Ast ast);
};
} // namespace ionir
