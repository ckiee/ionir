#pragma once

#include <vector>
#include <map>
#include "syntax/token_type.h"
#include "type_system/primitive_type.hpp"

namespace ionir
{
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
} // namespace ionir
