#include "bootstrap.h"

namespace ionir::test::bootstrap
{
Token token(TokenType type)
{
    return Token(type, "");
}

TokenStream tokenStream(int amountOfItems)
{
    std::vector<Token> tokens = {};

    // Populate the tokens vector.
    for (int i = 0; i < amountOfItems; i++)
    {
        tokens.push_back(token());
    }

    // Create the Stream and provide the tokens.
    return TokenStream(tokens);
}

Parser parser(std::vector<Token> tokens)
{
    ionir::TokenStream *stream = new ionir::TokenStream(tokens);

    return ionir::Parser(stream);
}

Module *module(std::string identifier)
{
    llvm::LLVMContext *llvmContext = new llvm::LLVMContext();
    llvm::Module *llvmModule = new llvm::Module("test", *llvmContext);

    return new Module(llvmModule);
}

LlvmVisitor *llvmVisitor()
{
    return new LlvmVisitor(module()->unwrap());
}
} // namespace ionir::test::bootstrap
