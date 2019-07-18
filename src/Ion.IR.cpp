#pragma once

#include <iostream>
#include <vector>
#include "Syntax/Lexer.hpp"

int main()
{
	std::cout << "Type ^ then ENTER to terminate." << std::endl;

	// Create a string to serve as iteration input buffer.
	std::string input;

	while (true)
	{
		std::cin >> input;

		if (input == "^")
		{
			break;
		}

		std::cout << "input >> " << input << std::endl;
		std::cout << "output >> ";

		// Create a new lexer.
		Lexer *lexer = new Lexer(input);

		// Tokenize the input.
		std::vector<Token> tokens = lexer->tokenize();

		for (auto iterator = tokens.begin(); iterator != tokens.end(); iterator++)
		{
			std::cout << *iterator;
		}

		std::cout << std::endl;
	}

	return 0;
}
