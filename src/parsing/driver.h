#pragma once

namespace ionir
{
class Driver : public LooseGenerator
{
private:
	TokenStream stream;

	llvm::Module *module;

public:
	Driver(llvm::Module *module, TokenStream stream);

	void consume();

	void begin() override;

	bool hasNext() const override;

	/**
	 * Processed the current iterable item and increments the
	 * list's index if applicable.
	 */
	void next() override;
};
} // namespace ionir
