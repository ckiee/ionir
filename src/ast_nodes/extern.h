#pragma once

#include <memory>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_nodes/prototype.h"

namespace ionir
{
class Pass;

class Extern : public Node
{
private:
	std::shared_ptr<Prototype> prototype;

public:
	Extern(std::shared_ptr<Prototype> prototype);

	std::shared_ptr<Node> accept(Pass *visitor) override;

	std::shared_ptr<Prototype> getPrototype() const;

	void setPrototype(std::shared_ptr<Prototype> prototype);
};
} // namespace ionir
