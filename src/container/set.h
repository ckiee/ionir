#pragma once

#include <set>
#include "misc/wrapper.h"

namespace ionir {
    template<typename T>
    class Set : public Wrapper<std::set<T>> {
    public:
        Set(std::set<T> value = {}) : Wrapper<T>(value) {
            //
        }

        bool insert(T item) {
            return this->value.insert(item);
        }

        bool contains(T item) {
            return this->value.find(item) != this->value.end();
        }

        size_t size() {
            return this->value.size();
        }

        void clear() {
            this->value.clear();
        }
    };
};
