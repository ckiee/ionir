#pragma once

#include <map>
#include <string>
#include "code_gen/node.h"

namespace ionir
{
class GlobalSpace
{
private:
	std::map<std::string, Node> variables;

public:
	bool hasVariable(std::string name) const;
};
} // namespace ionir
