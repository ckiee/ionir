#pragma once

#include <vector>
#include "Syntax/TokenType.hpp"

class Identifier
{
private:
    std::vector<TokenType> *primitiveTypes;

public:
    Identifier()
    {
        this->primitiveTypes = {
            TokenType::
        };
    }

    bool isPrimitiveType()
    {
    }
};
