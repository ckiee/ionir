#pragma once

#include <string>
#include <vector>
#include "construct/type.h"
#include "construct/psuedo/args.h"
#include "construct/construct.h"
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

	void setId(std::string id);

	Ptr<Args> getArgs() const;

	void setArgs(Ptr<Args> args);

	Ptr<Type> getReturnType() const;

	void setReturnType(Ptr<Type> returnType);

	bool verify() const override;
};
} // namespace ionir
