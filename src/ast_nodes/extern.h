#pragma once

namespace ionir
{
class Extern : public Node
{
private:
	Prototype prototype;

public:
	Extern(Prototype prototype);

	Node *accept(LlvmVisitor *visitor) override;

	Prototype getPrototype() const;
};
} // namespace ionir
