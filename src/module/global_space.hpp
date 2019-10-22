#pragma once

#include <map>
#include <string>

namespace ionir
{
class GlobalSpace
{
private:
	std::map<std::string, Expr> variables;

public:
	bool hasVariable(std::string name)
	{
		return this->variables.get
	}
};
} // namespace ionir
