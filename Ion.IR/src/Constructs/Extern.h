#pragma once

#include "Generation/Construct.h"
#include "Generation/ConstructType.h"
#include "Constructs/Prototype.h"

class Extern : public Construct
{
private:
	Prototype prototype;

public:
	Extern(Prototype prototype) : Construct(ConstructType::Extern)
	{
		this->prototype = prototype;
	}

	Prototype getPrototype()
	{
		return this->prototype;
	}
};
