#pragma once

#include <string>
#include "syntax/token.h"
#include "ast_nodes/integer.h"

namespace ionir
{
class Parser
{
protected:
    TokenStream stream;

public:
    Parser(TokenStream stream)
    {
        this->stream = stream;
    }

    void parseInteger()
    {
        std::string tokenValue = this->stream.get().getValue();

        // Attempt to convert token's value to a long.
        long value = std::stol(tokenValue);

        LiteralInteger result = new LiteralInteger(value);

        this->stream.next();
    }
};
} // namespace ionir
