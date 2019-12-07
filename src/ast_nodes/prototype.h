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

	Args *args;

	Type *returnType;

public:
	Prototype(std::string id, Args *args, Type *returnType);

	~Prototype();

	Node *accept(Pass *visitor) override;

	std::string getId() const;

	Args *getArgs() const;

	Type *getReturnType() const;
};
} // namespace ionir
