#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/block.h"

namespace ionir
{
class Function : public Node
{
protected:
	Prototype prototype;

	Block body;

public:
	Function(Prototype prototype, Block body) : Node(NodeKind::Function), prototype(prototype), body(body)
	{
		this->prototype = prototype;
		this->body = body;
	}

	Node *accept(LlvmVisitor *visitor) override
	{
		return visitor->visitFunction(this);
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
