#pragma once

#include <vector>
#include <map>
#include "Syntax/TokenType.hpp"
#include "TypeSystem/PrimitiveType.hpp"

class Identifier
{
private:
    std::map<std::string, TokenType> *primitiveTypes;

public:
    Identifier()
    {
        // Register primitive types.
        this->primitiveTypes->insert("void", PrimitiveType::Void);
        this->primitiveTypes->insert("int", PrimitiveType::Integer32);
        this->primitiveTypes->insert("string", PrimitiveType::String);
        this->primitiveTypes->insert("char", PrimitiveType::Character);
    }

    bool isPrimitive(std::string value)
    {
        // TODO

        return false;
    }
};
