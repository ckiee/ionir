#pragma once

template <typename T>
class Stream
{
protected:
	int position;
	T items[];

public:
	T next() {
		return this->items[++this->position];
	}
};
