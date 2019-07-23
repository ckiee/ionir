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

	bool next()
	{
		Token token = this->stream.get();

		// TODO: Continue implementation.

		return false;
	}
};
