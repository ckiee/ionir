#pragma once

#include <optional>
#include <map>
#include <ionir/misc/wrapper.h>

namespace ionir {
    template<typename TKey, typename TValue>
    class Map : public Wrapper<std::map<TKey, TValue>> {
    public:
        Map(std::map<TKey, TValue> value = {}) : Wrapper<std::map<TKey, TValue>>(value) {
            //
        }

        TValue &operator[](TKey key) {
            return this->value[key];
        }

        bool contains(TKey key) const {
            return this->value.find(key) != this->value.end();
        }

        bool insert(TKey key, TValue value, bool overwrite = false) {
            if (this->contains(key) && !overwrite) {
                return false;
            }

            this->value[key] = value;

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

            if (!value.has_value()) {
                return defaultValue;
            }

            return *value;
        }

        void clear() {
            this->value.clear();
        }

        size_t getSize() const {
            return this->value.size();
        }
    };
}
