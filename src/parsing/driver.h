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
	Driver(llvm::Module *module, TokenStream stream) : module(module), stream(stream)
	{
		//
	}

	void consume()
	{
		while (this->stream.hasNext())
		{
			this->next();
		}

		// Process the last item.
		if (this->stream.getSize())
		{
			this->next();
		}
	}

	void begin() override
	{
		this->stream.begin();
	}

	bool hasNext() const override
	{
		// TODO
		return false;
	}

	/**
	 * Processed the current iterable item and increments the
	 * list's index if applicable.
	 */
	void next() override
	{
		// Retrieve the current token from the token stream.
		Token token = this->stream.get();

		// Function definition (Token should be a type name representing the function's return type).
		if (token.getType() == TokenType::Identifier)
		{
			// TODO
			std::cout << "Identifier token detected ~> Expecting function definition. (Token is considered function return type.)" << std::endl;
		}

		std::cout << "Token type:" << token.getType() << std::endl;

		// Advance the Stream's index if applicable.
		this->stream.next();
	}
};
} // namespace ionir
