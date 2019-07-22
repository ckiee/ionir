#pragma once

#include "llvm/IR/Module.h"
#include "Syntax/TokenStream.hpp"
#include "Syntax/Token.hpp"

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
