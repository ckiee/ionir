#pragma once

#include "generation/expr.hpp"
#include "generation/expr_type.hpp"
#include "expression/prototype.hpp"
#include "expression/block.hpp"

namespace ionir
{
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

	Prototype getPrototype() const
	{
		return this->prototype;
	}

	Block getBody() const
	{
		return this->body;
	}
};
} // namespace ionir
