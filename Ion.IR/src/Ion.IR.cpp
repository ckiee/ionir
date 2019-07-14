#pragma once

#include <iostream>
#include <vector>
#include "Syntax/Lexer.h"

int main()
{
	// Create a string to serve as iteration input buffer.
	std::string input;

	while (input != "^exit") {
		std::cin >> input;

		// Create a new lexer.
		Lexer* lexer = new Lexer(input);

		// Tokenize the input.
		std::vector<Token> tokens = lexer->tokenize();

		for (auto iterator = tokens.begin(); iterator != tokens.end(); iterator++) {
			std::cout << &*iterator;
		}
	}

	return 0;
}
