#pragma once

#include "code_gen/node.h"
#include "code_gen/node_type.h"

namespace ionir
{
class Prototype : public Node
{
private:
	std::string identifier;

	std::vector<std::pair<Type, std::string>> arguments;

	Type returnType;

	bool hasInfiniteArguments;

public:
	Prototype(std::string identifier, std::vector<std::pair<Type, std::string>> arguments, Type returnType, bool hasInfiniteArguments) : Node(NodeType::Prototype), returnType(returnType)
	{
		this->identifier = identifier;
		this->arguments = arguments;
		this->hasInfiniteArguments = hasInfiniteArguments;
	}

	Node accept(LlvmVisitor *visitor)
	{
		return visitor->visitPrototype(this);
	}

	std::string getIdentifier() const
	{
		return this->identifier;
	}

	std::vector<std::pair<Type, std::string>> getArguments() const
	{
		return this->arguments;
	}

	Type getReturnType() const
	{
		return this->returnType;
	}

	bool getHasInfiniteArguments() const
	{
		return this->hasInfiniteArguments;
	}
};
} // namespace ionir
