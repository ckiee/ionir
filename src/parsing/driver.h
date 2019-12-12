#pragma once

#include <memory>
#include <optional>
#include "code_gen/node.h"
#include "llvm/IR/Module.h"
#include "syntax/token.h"
#include "misc/iterable.h"
#include "misc/loose_generator.h"
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
	std::optional<std::shared_ptr<Node>> tryNext(); // override;
};
} // namespace ionir
