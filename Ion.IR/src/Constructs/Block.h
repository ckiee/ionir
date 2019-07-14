#pragma once

#include "Generation/Construct.h"
#include "Generation/ConstructType.h"

class Block : public Construct
{
private:
    std::string identifier;

	std::vector<Construct> insts;

public:
    Block(std::string identifier, std::vector<Construct> insts) : Construct(ConstructType::Block)
    {
        this->identifier = identifier;
		this->insts = insts;
    }

    Construct accept(LlvmVisitor *visitor)
    {
        return (*visitor).visitBlock(this);
    }

	std::vector<Construct> getInsts()
	{
		return this->insts;
	}

    std::string getIdentifier()
    {
        return this->identifier;
    }
};
