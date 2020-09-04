#pragma once

#include <llvm/IR/Value.h>
#include <ionshared/container/map.h>
#include <ionshared/misc/helpers.h>
#include <ionir/construct/construct.h>

namespace ionir {
    class LlvmEmittedEntities {
    private:
        ionshared::Map<ionshared::Ptr<Construct>, llvm::Value *> entities;

    public:
        LlvmEmittedEntities();

        bool add(const ionshared::Ptr<Construct> &construct, llvm::Value *llvmValue);

        [[nodiscard]] bool contains(ionshared::Ptr<Construct> construct) const;

        template<typename T = llvm::Value>
        [[nodiscard]] std::optional<T *> find(const ionshared::Ptr<Construct> &construct) {
            if (this->contains(construct)) {
                T *castResult = llvm::dyn_cast<T>(this->entities[construct]);

                if (castResult != nullptr) {
                    return castResult;
                }

                throw std::runtime_error("LLVM value cast failed");
            }

            return std::nullopt;
        }
    };
}
