#pragma once

namespace ionir
{
template <typename TKey, typename TValue>
class Map : public Wrapper<std::map<TKey, TValue>>
{
protected:
	std::map<TKey, TValue> innerMap;

public:
	std::map<TKey, TValue> unwrap() const override;

	bool contains(TKey key) const;

	void insert(TKey key, TValue value);

	std::optional<TValue> tryGet(TKey key);

	TValue getOrDefault(TKey key, TValue defaultValue);
};
} // namespace ionir
