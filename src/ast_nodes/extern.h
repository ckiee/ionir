#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_nodes/prototype.h"

namespace ionir
{
class Pass;

class Extern : public Node
{
private:
	Prototype *prototype;

public:
	Extern(Prototype *prototype);

	Node *accept(Pass *visitor) override;

	Prototype *getPrototype() const;
};
} // namespace ionir
