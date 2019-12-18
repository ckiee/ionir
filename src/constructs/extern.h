#pragma once

#include <memory>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
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

	Ptr<Construct> accept(Pass *visitor) override;

	Ptr<Prototype> getPrototype() const;
};
} // namespace ionir
