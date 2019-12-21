#pragma once

#include <map>
#include <string>
#include "construct/construct.h"

namespace ionir
{
class GlobalSpace
{
private:
	std::map<std::string, Construct> variables;

public:
	bool hasVariable(std::string name) const;
};
} // namespace ionir
