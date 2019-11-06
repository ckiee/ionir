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
	Function(Prototype prototype, Block body);

	Node *accept(LlvmVisitor *visitor) override;

	Prototype getPrototype() const;

	Block getBody() const;
};
} // namespace ionir
