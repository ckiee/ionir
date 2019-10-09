#pragma once

#include "llvm/IR/Module.h"
#include "Syntax/Token.hpp"
#include "Syntax/Stream.hpp"

class Driver
{
private:
	Stream<Token> stream;

	llvm::Module *module;

public:
	Driver(llvm::Module *module, Stream<Token> stream) : module(module), stream(stream)
	{
		//
	}

	void invoke()
	{
		while (this->stream.hasNext())
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
		Token token = this->stream.get();

		// Function definition (token should be a type name).
		if (token.getType() == TokenType::Identifier)
		{
			// TODO
			std::cout << "Identifier token detected" << std::endl;
		}

		std::cout << "Token type:" << token.getType() << std::endl;

		this->stream.next();

		return false;
	}
};
