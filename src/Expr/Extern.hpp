#pragma once

#include "Generation/Expr.hpp"
#include "Generation/ExprType.hpp"
#include "Constructs/Prototype.hpp"

class Extern : public Expr
{
private:
	Prototype prototype;

public:
	Extern(Prototype prototype) : Expr(ExprType::Extern), prototype(prototype)
	{
		this->prototype = prototype;
	}

	Prototype getPrototype()
	{
		return this->prototype;
	}
};
