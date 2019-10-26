#include <iostream>
#include <vector>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "syntax/lexer.hpp"
#include "syntax/stream.hpp"
#include "parsing/driver.hpp"

using namespace ionir;

void processStream(TokenStream stream)
{
    llvm::LLVMContext context = llvm::LLVMContext();

    // TODO
    // Create the module.
    llvm::Module *module = new llvm::Module("entry", context);

    // Create the driver.
    Driver *driver = new Driver(module, stream);

    // Consume the driver, processing all the Stream's tokens.
    driver->consume();

    //TODO: Display result(s).
    std::cout << "Driver has been invoked." << std::endl;
}

int main()
{
    std::cout << "Instructions: Type '^<ENTER>' to terminate and '&<ENTER>' to invoke driver." << std::endl;

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
            processStream(TokenStream(tokens));

            // Flush tokens.
            tokens.clear();

            continue;
        }

        std::cout << "[!] input >> " << input << std::endl;

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
