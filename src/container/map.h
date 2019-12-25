#pragma once

#include <optional>
#include <map>
#include "misc/wrapper.h"

namespace ionir {
    template<typename TKey, typename TValue>
    class Map : public Wrapper<std::map<TKey, TValue>> {
    public:
        Map() : Wrapper<std::map<TKey, TValue>>({}) {
            //
        }

        bool contains(TKey key) const {
            auto it = this->value.find(key);

            return it != this->value.end();
        }

        bool insert(TKey key, TValue value, bool overwrite = false) {
            if (this->contains(key) && !overwrite) {
                return false;
            }

            this->value.insert(key, value);

            return true;
        }

        bool remove(TKey key) {
            if (!this->contains(key)) {
                return false;
            }

            return this->value.erase(key);
        }

        std::optional<TValue> lookup(TKey key) {
            if (!this->contains(key)) {
                return std::nullopt;
            }

            return this->value[key];
        }

        TValue lookupOr(TKey key, TValue defaultValue) {
            std::optional<TValue> value = this->lookup(key);

            if (value.has_value()) {
                return value;
            }

            return defaultValue;
        }

        void clear() {
            this->value.clear();
        }
    };
}
