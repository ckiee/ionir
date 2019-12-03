#pragma once

#include <string>
#include <vector>
#include "ast_nodes/type.h"
#include "ast_nodes/args.h"
#include "code_gen/node.h"

namespace ionir
{
class Pass;

class Prototype : public Node
{
protected:
	std::string id;

	Args arguments;

	Type *returnType;

public:
	Prototype(std::string id, Args arguments, Type *returnType);

	Node *accept(Pass *visitor) override;

	std::string getId() const;

	Args getArguments() const;

	Type *getReturnType() const;
};
} // namespace ionir
