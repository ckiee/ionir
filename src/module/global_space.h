#pragma once

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
