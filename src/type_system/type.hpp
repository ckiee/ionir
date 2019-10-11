#pragma once

#include "primitive_type_kind.hpp"

template <typename T>
class Type {
protected:
	T value;

	int id;

public:
	Type(T value, int id) {
		this->value = value;
		this->id = id;
	}
};
