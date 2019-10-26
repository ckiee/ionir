#pragma once

#include "generation/expr.h"
#include "generation/expr_type.h"
#include "expression/prototype.h"

namespace ionir
{
class Extern : public Expr
{
private:
	Prototype prototype;

public:
	Extern(Prototype prototype) : Expr(ExprType::Extern), prototype(prototype)
	{
		this->prototype = prototype;
	}

	Prototype getPrototype() const
	{
		return this->prototype;
	}
};
} // namespace ionir
