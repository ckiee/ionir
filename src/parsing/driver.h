#pragma once

#include <optional>
#include "construct/construct.h"
#include "llvm/IR/Module.h"
#include "syntax/token.h"
#include "misc/iterable.h"
#include "misc/loose_generator.h"
#include "misc/helpers.h"
#include "ast.h"

namespace ionir
{
// TODO
class Driver // : public LooseGenerator
{
private:
	TokenStream stream;

	llvm::Module *module;

public:
	Driver(llvm::Module *module, TokenStream stream);

	Ast consume();

	void begin(); // override;

	bool hasNext() const; // override;

	/**
	 * Processed the current iterable item and increments the
	 * list's index if applicable.
	 */
	std::optional<Ptr<Construct>> tryNext(); // override;
};
} // namespace ionir
