#include "Stream.h"

using namespace std;

template <typename T>
class Stream
{
protected:
	int position;

	std::array<T> items;

	int size;

	int resolvePosition(int position) {
		if ()
	}

public:
	Stream(T items[]) {
		this->items = items;
		this->size = this->items.size();
	}

	T next() {
		return this->items[++this->position];
	}
};
