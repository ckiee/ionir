#pragma once

#include <string>
#include <vector>
#include "ast_nodes/type.h"
#include "code_gen/llvm_visitor.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class Prototype : public Node
{
private:
	std::string identifier;

	std::vector<std::pair<Type, std::string>> arguments;

	Type returnType;

	bool hasInfiniteArguments;

public:
	Prototype(std::string identifier, std::vector<std::pair<Type, std::string>> arguments, Type returnType, bool hasInfiniteArguments);

	Node *accept(LlvmVisitor *visitor) override;

	std::string getIdentifier() const;

	std::vector<std::pair<Type, std::string>> getArguments() const;

	Type getReturnType() const;

	bool getHasInfiniteArguments() const;
};
} // namespace ionir
