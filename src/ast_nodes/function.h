#pragma once

#include <memory>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/block.h"

namespace ionir
{
class Pass;

class Function : public Node
{
protected:
	std::shared_ptr<Prototype> prototype;

	std::shared_ptr<Block> body;

public:
	Function(std::shared_ptr<Prototype> prototype, std::shared_ptr<Block> body);

	std::shared_ptr<Node> accept(Pass *visitor) override;

	std::shared_ptr<Prototype> getPrototype() const;

	void setPrototype(std::shared_ptr<Prototype> prototype);

	std::shared_ptr<Block> getBody() const;

	void setBody(std::shared_ptr<Block> body);

	bool verify() const override;
};
} // namespace ionir
