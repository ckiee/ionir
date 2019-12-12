#pragma once

#include <set>
#include <memory>
#include "pass_manager_item.h"

namespace ionir
{
class PassManager
{
protected:
    std::set<std::unique_ptr<PassManagerItem>> passes;

    void visitAstNode(std::shared_ptr<Node> node, Pass *visitor);

public:
    PassManager();

    /**
     * Attempt to register a pass in the set.
     * Returns whether the provided pass was
     * successfully registered in the internal
     * set.
     */
    bool registerPass(std::unique_ptr<PassManagerItem> item);

    void run();
};
} // namespace ionir
