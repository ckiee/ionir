#pragma once

#include "Generation/Construct.hpp"
#include "Generation/ConstructType.hpp"
#include "Constructs/Prototype.hpp"

class Extern : public Construct
{
private:
	Prototype prototype;

public:
	Extern(Prototype prototype) : Construct(ConstructType::Extern), prototype(prototype)
	{
		this->prototype = prototype;
	}

	Prototype getPrototype()
	{
		return this->prototype;
	}
};
