#pragma once

#include "Generation/Construct.h"
#include "Generation/ConstructType.h"
#include "Constructs/Prototype.h"

class Function : public Construct
{
private:
	Prototype prototype;

	Block body;

public:
	Function(Prototype prototype, Block body) : Construct(ConstructType::Function)
	{
		this->prototype = prototype;
		this->body = body;
	}

	Prototype getPrototype()
	{
		return this->prototype;
	}

	Block getBody()
	{
		return this->body;
	}
};
