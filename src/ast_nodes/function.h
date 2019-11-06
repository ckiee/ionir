#pragma once

namespace ionir
{
class Function : public Node
{
protected:
	Prototype prototype;

	Block body;

public:
	Function(Prototype prototype, Block body);

	Node *accept(LlvmVisitor *visitor) override;

	Prototype getPrototype() const;

	Block getBody() const;
};
} // namespace ionir
