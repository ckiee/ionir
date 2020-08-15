#pragma once

#include <optional>
#include <ionir/misc/util.h>
#include "map.h"

namespace ionir {
    template<typename TFirst, typename TSecond>
    class BiMap {
    private:
        Map<TFirst, TSecond> firstMap;

        Map<TSecond, TFirst> secondMap;

    public:
        explicit BiMap(std::map<TFirst, TSecond> value = {})
            : firstMap(Map<TFirst, TSecond>(value)), secondMap(Map<TSecond, TFirst>(Util::flipMap<TFirst, TSecond>(value))) {
            //
        }

        bool insert(TFirst first, TSecond second, bool overwrite = false) {
            return this->firstMap.insert(first, second, overwrite)
                && this->secondMap.insert(second, first, overwrite);
        }

        bool insert(TSecond second, TFirst first, bool overwrite = false) {
            return this->insert(first, second, overwrite);
        }

        std::optional<TSecond> lookup(TFirst first) {
            return this->firstMap.lookup(first);
        }

        std::optional<TFirst> lookup(TSecond second) {
            return this->secondMap.lookup(second);
        }

        bool contains(TFirst first) const {
            return this->firstMap.contains(first);
        }

        bool contains(TSecond second) const {
            return this->secondMap.contains(second);
        }

        const Map<TFirst, TSecond> &getFirstMap() const {
            return this->firstMap;
        }

        const Map<TSecond, TFirst> &getSecondMap() const {
            return this->secondMap;
        }

        BiMap<TFirst, TSecond> merge(BiMap<TFirst, TSecond> other) {
            BiMap<TFirst, TSecond> firstMap = BiMap<TFirst, TSecond>();

            // TODO: Check for existing keys in both maps.

            for (const auto [key, value] : this->firstMap.unwrapConst()) {
                firstMap.insert(key, value);
            }

            for (const auto [key, value] : other.firstMap.unwrapConst()) {
                firstMap.insert(key, value);
            }

            return BiMap<TFirst, TSecond>(firstMap);
        }
    };
}
