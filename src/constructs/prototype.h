#pragma once

#include <memory>
#include <string>
#include <vector>
#include "constructs/type.h"
#include "constructs/psuedo/args.h"
#include "constructs/construct.h"
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

	void accept(Pass *visitor) override;

	std::string getId() const;

	Ptr<Args> getArgs() const;

	Ptr<Type> getReturnType() const;
};
} // namespace ionir
