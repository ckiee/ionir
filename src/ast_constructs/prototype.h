#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ast_constructs/type.h"
#include "ast_constructs/args.h"
#include "code_gen/node.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Prototype : public Construct
{
protected:
	std::string id;

	Ptr<Args> args;

	Ptr<Type> returnType;

public:
	Prototype(std::string id, Ptr<Args> args, Ptr<Type> returnType);

	Ptr<Construct> accept(Pass *visitor) override;

	std::string getId() const;

	void setId(std::string id);

	Ptr<Args> getArgs() const;

	void setArgs(Ptr<Args> args);

	Ptr<Type> getReturnType() const;

	void setReturnType(Ptr<Type> returnType);
};
} // namespace ionir
