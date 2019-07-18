#pragma once

#include "Generation/Construct.hpp"

class Prototype : public Construct
{
private:
	std::string identifier;

	std::vector<std::pair<Type, std::string>> arguments;

	Type returnType;

	bool hasInfiniteArguments;

public:
	Prototype(std::string identifier, std::vector<std::pair<Type, std::string>> arguments, Type returnType, bool hasInfiniteArguments) : Construct(ConstructType::Prototype), returnType(returnType)
	{
		this->identifier = identifier;
		this->arguments = arguments;
		this->hasInfiniteArguments = hasInfiniteArguments;
	}

    Construct accept(LlvmVisitor *visitor)
    {
        return visitor->visitPrototype(this);
    }

	std::string getIdentifier()
	{
		return this->identifier;
	}

	std::vector<std::pair<Type, std::string>> getArguments()
	{
		return this->arguments;
	}

	Type getReturnType()
	{
		return this->returnType;
	}

	bool getHasInfiniteArguments()
	{
		return this->hasInfiniteArguments;
	}
};
