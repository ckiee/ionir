#pragma once

#include "constructs/construct.h"
#include "constructs/construct_kind.h"
#include "constructs/prototype.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Extern : public Construct
{
private:
	Ptr<Prototype> prototype;

public:
	Extern(Ptr<Prototype> prototype);

	void accept(Pass *visitor) override;

	Ptr<Prototype> getPrototype() const;

	void setPrototype(Ptr<Prototype> prototype);
};
} // namespace ionir
