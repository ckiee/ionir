#pragma once

#include "code_gen/node.h"
#include "code_gen/node_type.h"
#include "nodes/prototype.h"
#include "nodes/block.h"

namespace ionir
{
class Function : public Node
{
protected:
	Prototype prototype;

	Block body;

public:
	Function(Prototype prototype, Block body) : Node(NodeType::Function), prototype(prototype), body(body)
	{
		this->prototype = prototype;
		this->body = body;
	}

	Prototype getPrototype() const
	{
		return this->prototype;
	}

	Block getBody() const
	{
		return this->body;
	}
};
} // namespace ionir
