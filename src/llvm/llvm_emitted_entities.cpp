#include <ionir/llvm/llvm_emitted_entities.h>

namespace ionir {
    LlvmEmittedEntities::LlvmEmittedEntities() :
        entities() {
        //
    }

    bool LlvmEmittedEntities::add(const ionshared::Ptr<Construct> &construct, llvm::Value *llvmValue) {
        if (!this->contains(construct)) {
            return this->entities.insert(construct, llvmValue);
        }

        return false;
    }

    bool LlvmEmittedEntities::contains(ionshared::Ptr<Construct> construct) const {
        return this->entities.contains(std::move(construct));
    }
}
