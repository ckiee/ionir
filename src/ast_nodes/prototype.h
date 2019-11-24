#pragma once

#include <string>
#include <vector>
#include "ast_nodes/type.h"
#include "ast_nodes/args.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class LlvmVisitor;

class Prototype : public Node
{
private:
	std::string identifier;

	Args arguments;

	Type *returnType;

public:
	Prototype(std::string identifier, Args arguments, Type *returnType);

	Node *accept(LlvmVisitor *visitor) override;

	std::string getIdentifier() const;

	Args getArguments() const;

	Type *getReturnType() const;
};
} // namespace ionir
