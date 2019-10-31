#pragma once

#include "primitive_type.h"

namespace ionir
{
template <typename T>
class Type
{
protected:
	T value;

	int id;

public:
	Type(T value, int id)
	{
		this->value = value;
		this->id = id;
	}
};
} // namespace ionir