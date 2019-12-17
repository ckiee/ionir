#pragma once

#include <memory>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/block.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Function : public Node
{
protected:
	Ptr<Prototype> prototype;

	Ptr<Block> body;

public:
	Function(Ptr<Prototype> prototype, Ptr<Block> body);

	Ptr<Node> accept(Pass *visitor) override;

	Ptr<Prototype> getPrototype() const;

	void setPrototype(Ptr<Prototype> prototype);

	Ptr<Block> getBody() const;

	void setBody(Ptr<Block> body);

	bool verify() const override;
};
} // namespace ionir
