#include <iostream>
#include <vector>
#include "llvm/IR/Module.h"
#include "Syntax/Lexer.hpp"
#include "Parsing/Driver.hpp"

void processTokens(std::vector<Token> tokens)
{
	// TODO
	// Create the module.
	llvm::Module *module = llvm::Module();

	// Create the driver.
	Driver *driver = new Driver(*module, &tokens);

	// Invoke the driver.
	driver->invoke();

	// TODO: Display result(s).
}

int main()
{
	std::cout << "Type ^ then ENTER to terminate, & to invoke driver." << std::endl;

	// Create a string to serve as iteration input buffer.
	std::string input;

	// Create a vector for the resulting tokens.
	std::vector<Token> tokens;

	while (true)
	{
		std::cin >> input;

		if (input == "^")
		{
			break;
		}
		else if (input == "&")
		{
			// Delegate to process tokens.
			processTokens(tokens);

			// Flush tokens.
			tokens.clear();

			continue;
		}

		std::cout << "input >> " << input << std::endl;
		std::cout << "output >> " << std::endl;

		// Create a new lexer.
		Lexer *lexer = new Lexer(input);

		// Tokenize the input.
		std::vector<Token> batch = lexer->tokenize();

		// Iterate and output resulting tokens.
		for (auto iterator = batch.begin(); iterator != batch.end(); iterator++)
		{
			std::cout << *iterator << std::endl;

			// Append the token onto the result.
			tokens.push_back(*iterator);
		}
	}

	return 0;
}
