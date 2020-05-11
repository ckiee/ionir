#pragma once

#include <llvm/Support/Casting.h>
#include "stack.h"

namespace ionir {
    template<typename T>
    class LlvmStack : public Stack<T *> {
    public:
        template<typename TResult>
        TResult *popAs() {
            return llvm::dyn_cast<TResult>(this->pop());
        }
    };
}
