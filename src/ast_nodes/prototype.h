#pragma once

#include <memory>
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

	std::shared_ptr<Args> args;

	std::shared_ptr<Type> returnType;

public:
	Prototype(std::string id, std::shared_ptr<Args> args, std::shared_ptr<Type> returnType);

	std::shared_ptr<Node> accept(Pass *visitor) override;

	std::string getId() const;

	std::shared_ptr<Args> getArgs() const;

	std::shared_ptr<Type> getReturnType() const;
};
} // namespace ionir
