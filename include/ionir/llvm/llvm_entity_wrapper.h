#pragma once

#include <ionir/misc/wrapper.h>

namespace ionir {
    template<typename T>
    class LlvmEntityWrapper : public Wrapper<T> {
    public:
        explicit LlvmEntityWrapper(T value) : Wrapper<T>(value) {
            if (value == nullptr) {
                throw std::runtime_error("Cannot construct LLVM entity wrapper with a null value");
            }
        }
    };
}
