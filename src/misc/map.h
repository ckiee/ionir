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

        void insert(TKey key, TValue value) {
            this->value.insert(key, value);
        }

        std::optional<TValue> tryGet(TKey key) {
            if (this->contains(key)) {
                return this->value[key];
            }

            return std::nullopt;
        }

        TValue getOrDefault(TKey key, TValue defaultValue) {
            std::optional<TValue> value = this->tryGet(key);

            if (value.has_value()) {
                return value;
            }

            return defaultValue;
        }
    };
}
