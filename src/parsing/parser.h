#pragma once

#include <exception>
#include <limits>
#include <string>
#include "syntax/token.h"
#include "ast_nodes/integer.h"

namespace ionir
{
class Parser
{
protected:
    TokenStream stream;

    bool withinRange(long value, long from, long to)
    {
        return value >= from && value <= to;
    }

public:
    Parser(TokenStream stream) : stream(stream)
    {
        //
    }

    /**
     * Parses a literal integer in the form of
     * long (or integer 64).
     */
    LiteralInteger parseInteger()
    {
        // Abstract the token's value to be used in the string -> long conversion.
        std::string tokenValue = this->stream.get().getValue();

        // Attempt to convert token's value to a long.
        long value = std::stol(tokenValue);

        std::optional<IntegerKind> kind = std::nullopt;

        if (this->withinRange(value, SHRT_MIN, SHRT_MAX))
        {
            kind = IntegerKind::Int16;
        }
        else if (this->withinRange(value, INT_MIN, INT_MAX))
        {
            kind = IntegerKind::Int32;
        }
        else if (this->withinRange(value, LONG_MIN, LONG_MAX))
        {
            kind = IntegerKind::Int64;
        }
        // TODO: Missing Int128.
        else
        {
            throw std::exception("Unable to identify integer kind for value");
        }

        // At this point, kind must be set.
        if (!kind.has_value())
        {
            throw std::exception("Expected kind to be defined");
        }

        // Create the integer instance.
        LiteralInteger result = LiteralInteger(kind.value, value);

        // Skip current token.
        this->stream.next();

        // Finally, return the result.
        return result;
    }
};
} // namespace ionir
