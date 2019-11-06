#pragma once

#include <optional>
#include "llvm/IR/Module.h"
#include "syntax/token.h"
#include "misc/iterable.h"
#include "misc/loose_generator.h"

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
