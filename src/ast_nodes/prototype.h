#pragma once

namespace ionir
{
class Prototype : public Node
{
private:
	std::string identifier;

	std::vector<std::pair<Type, std::string>> arguments;

	Type returnType;

	bool hasInfiniteArguments;

public:
	Prototype(std::string identifier, std::vector<std::pair<Type, std::string>> arguments, Type returnType, bool hasInfiniteArguments);

	Node *accept(LlvmVisitor *visitor) override;

	std::string getIdentifier() const;

	std::vector<std::pair<Type, std::string>> getArguments() const;

	Type getReturnType() const;

	bool getHasInfiniteArguments() const;
};
} // namespace ionir
