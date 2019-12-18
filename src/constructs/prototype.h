#pragma once

#include <memory>
#include <string>
#include <vector>
#include "constructs/type.h"
#include "constructs/args.h"
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

	Ptr<Args> getArgs() const;

	Ptr<Type> getReturnType() const;
};
} // namespace ionir
