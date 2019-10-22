#pragma once

#include <map>

namespace ionir
{
template typename<TKey> template typename<TValue> class Map
{
public:
	std::map<TKey, TValue> innerMap;

	bool contains(TKey key)
	{
		return this
	}
};
} // namespace ionir
