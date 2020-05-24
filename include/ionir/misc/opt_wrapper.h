#pragma once

#include <optional>
#include "util.h"

namespace ionir {
    template<typename T>
    class OptWrapper : public Wrapper<std::optional<T>> {
    protected:
        T value;

    public:
        explicit OptWrapper(std::optional<T> value) : Wrapper<std::optional<T>>(value) {
            //
        }

        bool hasValue() noexcept {
            return Util::hasValue(this->value);
        }
    };
}
