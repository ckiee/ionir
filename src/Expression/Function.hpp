#pragma once

#include "Generation/Expr.hpp"
#include "Generation/ExprType.hpp"
#include "Expression/Prototype.hpp"
#include "Expression/Block.hpp"

class Function : public Expr
{
private:
	Prototype prototype;

	Block body;

public:
	Function(Prototype prototype, Block body) : Expr(ExprType::Function), prototype(prototype), body(body)
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
