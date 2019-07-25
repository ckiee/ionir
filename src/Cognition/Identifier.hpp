#pragma once

#include <vector>
#include <map>
#include "Syntax/TokenType.hpp"

class Identifier
{
private:
    std::map<std::string, TokenType> *primitiveTypes;

public:
    Identifier()
    {
        // Register primitive types.
        this->primitiveTypes.insert(std::make_pair("void", PrimitiveType::Void));
        this->primitiveTypes.insert(std::make_pair("int", PrimitiveType::Integer32));
        this->primitiveTypes.insert(std::make_pair("string", PrimitiveType::String));
        this->primitiveTypes.insert(std::make_pair("char", PrimitiveType::Character));
    }

    bool isPrimitive(std::string value)
    {
        // TODO

        return false;
    }
};
