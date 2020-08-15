#pragma once

#include <set>
#include <ionir/misc/wrapper.h>

namespace ionir {
    template<typename T>
    class Set : public Wrapper<std::set<T>> {
    public:
        explicit Set(std::set<T> value = {}) : Wrapper<std::set<T>>(value) {
            //
        }

        bool insert(T item) {
            if (this->contains(item)) {
                return false;
            }

            /**
             * TODO: std::set's native insert() method returns
             * a pair (and possibly nullptr if it failed)? If so,
             * determine result through it.
             */
            this->value.insert(item);

            return true;
        }

        bool contains(T item) const {
            return this->value.find(item) != this->value.end();
        }

        size_t size() const {
            return this->value.size();
        }

        void clear() {
            this->value.clear();
        }
    };
};
