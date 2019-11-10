#pragma once

#include <optional>
#include <map>
#include "misc/wrapper.h"

namespace ionir
{
template <typename TKey, typename TValue>
class Map : public Wrapper<std::map<TKey, TValue>>
{
protected:
	std::map<TKey, TValue> innerMap;

public:
	Map::Map()
	{
		// TODO: Initialize 'innerMap.'
	}

	std::map<TKey, TValue> Map::unwrap() const
	{
		return this->innerMap;
	}

	bool Map::contains(TKey key) const
	{
		auto it = this->innerMap.find(key);

		if (it != this->innerMap.end())
		{
			return true;
		}

		return false;
	}

	void Map::insert(TKey key, TValue value)
	{
		this->innerMap.insert(key, value);
	}

	std::optional<TValue> Map::tryGet(TKey key)
	{
		if (this->contains(key))
		{
			return this->innerMap[key];
		}

		return std::nullopt;
	}

	TValue Map::getOrDefault(TKey key, TValue defaultValue)
	{
		std::optional<TValue> value = this->tryGet(key);

		if (value.has_value())
		{
			return value;
		}

		return defaultValue;
	}
};
} // namespace ionir
