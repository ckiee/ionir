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
	std::string identifier;

	Args arguments;

	Type *returnType;

public:
	Prototype(std::string identifier, Args arguments, Type *returnType);

	Node *accept(Pass *visitor) override;

	std::string getIdentifier() const;

	Args getArguments() const;

	Type *getReturnType() const;
};
} // namespace ionir
