#include "driver.h"

namespace ionir
{
Driver::Driver(llvm::Module *module, TokenStream stream) : module(module), stream(stream)
{
    //
}

void Driver::consume()
{
    while (this->stream.hasNext())
    {
        this->tryNext();
    }

    // Process the last item.
    if (this->stream.getSize())
    {
        this->tryNext();
    }
}

void Driver::begin()
{
    this->stream.begin();
}

bool Driver::hasNext() const
{
    // TODO
    return false;
}

void Driver::tryNext()
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
    this->stream.tryNext();
}
} // namespace ionir
