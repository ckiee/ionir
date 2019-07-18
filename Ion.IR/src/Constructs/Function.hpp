#pragma once

#include "Generation/Construct.hpp"
#include "Generation/ConstructType.hpp"
#include "Constructs/Prototype.hpp"
#include "Constructs/Block.hpp"

class Function : public Construct
{
private:
	Prototype prototype;

	Block body;

public:
	Function(Prototype prototype, Block body) : Construct(ConstructType::Function), prototype(prototype), body(body)
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
