#pragma once

#include "llvm/IR/Module.h"
#include "syntax/token.hpp"
#include "syntax/stream.hpp"

namespace ionir
{
class Driver
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

	/**
	 * Processed the current Stream item and increments the
	 * Stream's index if applicable.
	 */
	bool next()
	{
		// Retrieve the current item (Token) from the Stream.
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

		return false;
	}
};
} // namespace ionir
