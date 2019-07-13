#pragma once

#include <map>
#include <string>
#include "Syntax/TokenType.hh"

class TokenConstants
{
private:
    std::map<std::string, TokenType> symbols;

public:
    TokenConstants()
    {
        // Initialize symbols map.
        this->symbols["@", TokenType::];
    }
};
