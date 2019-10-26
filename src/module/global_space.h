#pragma once

#include <map>
#include <string>
#include "generation/expr.h"

namespace ionir
{
class GlobalSpace
{
private:
	std::map<std::string, Expr> variables;

public:
	bool hasVariable(std::string name) const
	{
		// TODO: Finish implementation.
		return this->variables.get
	}
};
} // namespace ionir
