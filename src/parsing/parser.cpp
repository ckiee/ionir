#include <exception>
#include "parser.h"

namespace ionir
{
bool Parser::withinRange(long value, long from, long to)
{
    return value >= from && value <= to;
}

void Parser::expect(TokenType type)
{
    Token current = this->stream.get();

    if (current.getType() != type)
    {
        throw std::runtime_error("Unexpected token type");
    }
}

Parser::Parser(TokenStream stream) : stream(stream)
{
    //
}

/**
 * Parses a literal integer in the form of
 * long (or integer 64).
 */
LiteralInteger *Parser::parseInteger()
{
    this->expect(TokenType::LiteralInteger);

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
        throw std::runtime_error("Unable to identify integer kind for value");
    }

    // At this point, kind must be set.
    if (!kind.has_value())
    {
        throw std::runtime_error("Expected kind to be defined");
    }

    // Create the integer instance.
    LiteralInteger result = LiteralInteger(*kind, value);

    // Skip current token.
    this->stream.next();

    // Finally, return the result.
    return &result;
}

Extern *Parser::parseExtern()
{
    this->expect(TokenType::KeywordExtern);
    this->stream.next();
    this->expect(TokenType::Identifier);
    this->stream.next();

    // TODO: Finish implementation.
    return nullptr;
}
} // namespace ionir
