#pragma once

#include <memory>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "constructs/prototype.h"
#include "constructs/block.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Function : public Construct
{
protected:
	Ptr<Prototype> prototype;

	Ptr<Block> body;

public:
	Function(Ptr<Prototype> prototype, Ptr<Block> body);

	Ptr<Construct> accept(Pass *visitor) override;

	Ptr<Prototype> getPrototype() const;

	void setPrototype(Ptr<Prototype> prototype);

	Ptr<Block> getBody() const;

	void setBody(Ptr<Block> body);

	bool verify() const override;
};
} // namespace ionir
