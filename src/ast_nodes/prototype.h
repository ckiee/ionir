#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class Prototype : public Node
{
private:
	std::string identifier;

	std::vector<std::pair<Type, std::string>> arguments;

	std::unique_ptr<Type> returnType;

	bool hasInfiniteArguments;

public:
	Prototype(std::string identifier, std::vector<std::pair<Type, std::string>> arguments, std::unique_ptr<Type> returnType, bool hasInfiniteArguments) : Node(NodeKind::Prototype)
	{
		this->identifier = identifier;
		this->arguments = arguments;
		this->returnType = returnType;
		this->hasInfiniteArguments = hasInfiniteArguments;
	}

	NodePtr accept(LlvmVisitor *visitor) override
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

	std::unique_ptr<Type> getReturnType() const
	{
		return this->returnType;
	}

	bool getHasInfiniteArguments() const
	{
		return this->hasInfiniteArguments;
	}
};
} // namespace ionir
