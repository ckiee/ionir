#include <ionir/syntax/driver.h>
#include <ionir/passes/pass_manager.h>

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

    void PassManager::run(Ast

    ast) {
    for (

    const auto item

    : this->passes) {
    // TODO: Process priorities.
    for (

    auto topLevelConstruct

    : ast) {
    item.pass->

    visit(topLevelConstruct);
}
}
}
}
