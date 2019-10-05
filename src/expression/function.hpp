#pragma once

#include "generation/expr.hpp"
#include "generation/expr_type.hpp"
#include "expression/prototype.hpp"
#include "expression/block.hpp"

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
