#pragma once

#include <set>
#include "misc/wrapper.h"

namespace ionir {
    template<typename T>
    class Set : public Wrapper<std::set<T>> {
    public:
        bool insert(T item) {
            return this->value.insert(item);
        }

        bool contains(T item) {
            return this->value.find(item) != this->value.end();
        }
    };
};
