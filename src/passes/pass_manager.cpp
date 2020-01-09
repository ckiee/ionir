#include <queue>
#include <ionir/passes/pass_manager.h>
#include <ionir/passes/pass.h>

namespace ionir {
    PassManager::PassManager(std::vector<PassManagerItem> passes) : passes(passes) {
        //
    }

    std::vector<PassManagerItem> &PassManager::getPasses() {
        return this->passes;
    }

    void PassManager::setPasses(std::vector<PassManagerItem> passes) {
        this->passes = passes;
    }

    void PassManager::registerPass(PassManagerItem item) {
        this->passes.push_back(item);
    }

    void PassManager::registerPass(Ptr<Pass> pass) {
        this->registerPass(PassManagerItem{
            pass
        });
    }

    void PassManager::run(Ast ast) {
        auto compare = [](PassManagerItem left, PassManagerItem right) {
            // TODO: Ensure correct order.
            return left.priority > right.priority;
        };

        std::priority_queue<
            PassManagerItem,
            std::vector<PassManagerItem>,
            decltype(compare)
        > runQueue(compare);

        // Push pass manager items onto the queue, thus ordering them.
        for (const auto item : this->passes) {
            runQueue.push(item);
        }

        /**
         * Loop through the resulting ordered queue
         * and start executing passes.
         */
        while (!runQueue.empty()) {
            PassManagerItem item = runQueue.top();

            runQueue.pop();

            for (auto &topLevelConstruct : ast) {
                item.pass->visit(topLevelConstruct);
            }
        }
    }
}
